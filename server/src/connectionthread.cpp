#include "connectionthread.h"

#include <QHostAddress>
#include <QEventLoop>
#include <QSet>

#include "server.h"
#include "fbsync.h"
#include "event.h"
#include "comment.h"

const QMap<MessCodes, ConnectionThread::mem_func> ConnectionThread::_actions = {
	{MessCodes::login, &ConnectionThread::login},
	{MessCodes::signup, &ConnectionThread::signup},
	{MessCodes::user_data, &ConnectionThread::userData},
	{MessCodes::friends_list, &ConnectionThread::friendsList},
	{MessCodes::event_data, &ConnectionThread::eventData},
	{MessCodes::create_event, &ConnectionThread::createEvent},
	{MessCodes::update_event, &ConnectionThread::updateEvent},
	{MessCodes::join_event, &ConnectionThread::joinEvent},
	{MessCodes::add_friend, &ConnectionThread::addFriend},
	{MessCodes::del_friend, &ConnectionThread::delFriend},
	{MessCodes::fb_friends_list, &ConnectionThread::fbFriendsList},
	{MessCodes::comment_data, &ConnectionThread::commentData},
	{MessCodes::add_comment, &ConnectionThread::addComment},
	{MessCodes::update_comment, &ConnectionThread::updateComment},
	{MessCodes::del_comment, &ConnectionThread::delComment},
	{MessCodes::create_userDEBUG, &ConnectionThread::createUserDbg},
	{MessCodes::del_user, &ConnectionThread::delUser}
};

ConnectionThread::ConnectionThread(Server *parent, int id, QWaitCondition& wait) : QThread(parent), _parent(parent), _id(id), _stream(), _user(nullptr), _db(new DBController(_id)), _mtx(),_wait(wait)
{
}

ConnectionThread::~ConnectionThread()
{
	if (_user) {
		delete _user;
	}
	if (_db) {
		delete _db;
	}
}

void ConnectionThread::run()
{
	qDebug()<<"Thread started\n" << QThread::currentThreadId();

	this->setAutoDelete(false);

	_mtx.lock();
	_wait.wait(&_mtx);
	qintptr id = _parent->nextClient();
	_socket_desc = id;
	handleConnection();

	exec();
}

void ConnectionThread::handleConnection()
{
	_socket = new QTcpSocket();

	_stream.setDevice(_socket);

	if (!_socket->setSocketDescriptor(this->_socket_desc)) {
		emit error(_socket->error());
		return;
	}

	connect(this->_socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
	connect(this->_socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

	qDebug()<<_socket_desc<<"Client connected\n";

	qDebug()<<_socket->peerName()<<" "<<_socket->peerAddress()<<" "<<_socket->peerPort()<<endl;
}

void ConnectionThread::readyRead()
{
	qDebug() << "readyRead";

	/* needs to be added in release */
	if (!_user) {
		signup();
	}
	else {
		MessCodes m_code;

		_stream >> m_code;

		if (m_code != MessCodes::error)
			qDebug()<<"m_code: "<<(qint32)m_code;
		else
			qDebug()<<"error\n";

		auto it = _actions.find(m_code);
		if (it != _actions.end()) {
			(this->**it)();
		}
		else
			qDebug()<<"error\n";
		if (_socket->bytesAvailable() > 0) {
			this->readyRead();
		}
	}
}

void ConnectionThread::disconnected()
{
	qDebug()<<_socket_desc<<"Disconnected";

	_socket->deleteLater();
	_socket = 0;

	if (!_parent->clientWaiting()) {
		_mtx.lock();
		_wait.wait(&_mtx);
	}
	_socket_desc = _parent->nextClient();
	handleConnection();
}

/* for testing, wont be included in release */
void ConnectionThread::login()
{
	qDebug() << "login";
	while (_socket->bytesAvailable() < sizeof(id_type)) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}
	id_type user_id;
	_stream >> user_id;
	_user = _db->getUserById(user_id);
	if (_user) {
		qDebug() << "logged: " << _user->firstName() << _user->lastName();
		sendOK();
	}
	else {
		sendError();
	}
}

void ConnectionThread::signup()
{
	qDebug()<<"signup";

	while (_socket->bytesAvailable() < sizeof(qint32)) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}

	qint32 size;
	_stream >> size;
	while (_socket->bytesAvailable() < size) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}

	QString token(size);
	_stream >> token;

	FBsync fb;
	fb.setToken(token);

	QEventLoop loop;
	connect(&fb,SIGNAL(userDataReady()),&loop,SLOT(quit()));
	connect(&fb,SIGNAL(error()),&loop,SLOT(quit()));
	fb.fetchData();
	loop.exec();

	if (fb.wasError()) {
		sendError();
		_socket->disconnectFromHost();
		return;
	}

	User u = fb.getUser();

	_user = _db->getUserById(u.id());
	id_type id;
	if (!_user) {
		for (auto f : u.friends()) {
			if (!_db->getUserById(f)) {
				u.delFriend(f);
			}
		}
		_db->createUser(u);
		id = u.id();
		_user = _db->getUserById(id);
	}
	else {
		id = _user->id();
	}

	sendOK();
	_stream << id;
	_socket->flush();
}

void ConnectionThread::userData()
{
	qDebug()<<"userData";

	while (_socket->bytesAvailable() < sizeof(id_type)) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}

	id_type user_id;
	_stream >> user_id;
	if (user_id == _user->id()) {
		_stream << *_user;
	}
	else {
		User *u = _db->getUserById(user_id);
		if (u) {
			_stream << *u;
			delete u;
		}
		else {
			User u;
			_stream << u;
		}
	}
	_socket->flush();
}

void ConnectionThread::delUser()
{
	qDebug() << "delUser";

	if (_user) {
		_db->removeUser(*_user);
		sendOK();
	}
	else {
		sendError();
	}
	_socket->disconnectFromHost();
}

void ConnectionThread::friendsList()
{
	qDebug()<<"friendsList";

	while (_socket->bytesAvailable() < sizeof(id_type)) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}

	id_type user_id;
	_stream >> user_id;
	if (user_id == _user->id()) {
		_stream << _user->friends();
	}
	else {
		User *u = _db->getUserById(user_id);
		if (u) {
			_stream << u->friends();
		}
		else {
			User u;
			_stream << u.friends();
		}
	}
	_socket->flush();
}

void ConnectionThread::eventData()
{
	qDebug()<<"eventData";

	while (_socket->bytesAvailable() < sizeof(id_type)) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}

	id_type event_id;
	_stream >> event_id;
	Event *e = _db->getEvent(event_id);
	if (e) {
		if (!e->id())
			qDebug() << "ERROR: Event id = 0";
		_stream << *e;
	}
	else {
		Event e;
		_stream << e;
	}
	_socket->flush();
	delete e;
}

void ConnectionThread::createEvent()
{
	qDebug()<<"createEvent";

	Event e = Event::readEvent(_socket);

	QList<id_type> l = _user->friends();

	e.setInvited(l);

	e.addAttendant(_user->id());

	auto eid = _db->createEvent(e);
	if (!_db->getEvent(eid)) {
		sendError();
		return;
	}
	id_type id = _user->id();
	delete _user;
	this->_user = _db->getUserById(id);
	sendOK();
}

void ConnectionThread::updateEvent()
{
	qDebug()<<"updateEvent";

	Event e = Event::readEvent(_socket);

	if (_db->getEvent(e.id())) {
		_db->updateEvent(e);
		sendOK();
	}
	else {
		sendError();
	}
}

void ConnectionThread::joinEvent()
{
	qDebug()<<"joinEvent";

	while (_socket->bytesAvailable() < sizeof(id_type)) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}

	id_type id;
	_stream >> id;

	Event *e = _db->getEvent(id);

	if (e) {
		e->addInvited(_user->id());
		e->addAttendant(_user->id());
		_db->updateEvent(*e);
		delete e;
		id_type uid = _user->id();
		delete _user;
		_user = _db->getUserById(uid);
		sendOK();
	}
	else {
		sendError();
	}
}

void ConnectionThread::addFriend()
{
	qDebug()<<"addFriend";

	while (_socket->bytesAvailable() < sizeof(id_type)) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}

	id_type id;
	_stream >> id;
	this->_user->addFriend(id);
	_db->updateUser(*_user);
	id_type uid = _user->id();
	delete _user;
	_user = _db->getUserById(uid);
	sendOK();
}

void ConnectionThread::delFriend()
{
	qDebug()<<"delFriend";

	while (_socket->bytesAvailable() < sizeof(id_type)) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}

	id_type id;
	_stream >> id;
	this->_user->delFriend(id);
	_db->updateUser(*_user);
	id_type mid = _user->id();
	delete _user;
	_user = _db->getUserById(mid);
	sendOK();
}

void ConnectionThread::fbFriendsList()
{
	qDebug()<<"fb_friends";

	while (_socket->bytesAvailable() < sizeof(qint32)) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}

	qint32 size;
	_stream >> size;

	while (_socket->bytesAvailable() < size) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}

	QString token;
	_stream >> token;

	FBsync fb;
	fb.setToken(token);

	QEventLoop loop;
	connect(&fb,SIGNAL(userDataReady()),&loop,SLOT(quit()), Qt::QueuedConnection);
	fb.fetchData();
	loop.exec();

	QList<id_type> fb_list = fb.friendsList();
	QList<id_type> user_list = _user->friends();

	QSet<id_type> fb_set = QSet<id_type>::fromList(fb_list);
	QSet<id_type> fb_set_tmp = QSet<id_type>::fromList(fb_list);
	QSet<id_type> user_set = QSet<id_type>::fromList(user_list);
	QSet<id_type> intersect = fb_set_tmp.intersect(user_set);
	fb_set.subtract(intersect);

	auto fb_list_r = fb_set.toList();

	_stream << fb_list_r.size();
	_socket->waitForBytesWritten();
	_stream << fb_set.toList();
	_socket->flush();
}

void ConnectionThread::commentData()
{
	qDebug() << "commentData";

	while (_socket->bytesAvailable() < sizeof(id_type)) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}

	id_type id;

	_stream >> id;

	Comment *c = _db->getComment(id);

	if (c) {
		_stream << *c;
		delete c;
	}
	else {
		Comment c;
		_stream << c;
	}
}

void ConnectionThread::addComment()
{
	qDebug() << "addComment";

	Comment c = Comment::readComment(_socket);

	_db->createComment(c);

	sendOK();
}

void ConnectionThread::updateComment()
{
	qDebug() << "updateComment";

	Comment c = Comment::readComment(_socket);

	_db->updateComment(c);

	sendOK();
}

void ConnectionThread::delComment()
{
	qDebug() << "delComment";

	while (_socket->bytesAvailable() < sizeof(qint32)) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}

	id_type cid;
	_stream >> cid;

	Comment *c = _db->getComment(cid);
	_db->removeComment(*c);

	delete c;

	sendOK();
}

void ConnectionThread::createUserDbg()
{
	qDebug() << "createUserDbg";

	User u = User::readUser(_socket);

	_db->createUser(u);

	sendOK();
}

void ConnectionThread::sendOK()
{
	_stream << MessCodes::ok;
	_socket->flush();
	_socket->waitForBytesWritten();
	if (_socket->bytesAvailable() > 0) {
		this->readyRead();
	}
}

void ConnectionThread::sendError()
{
	_stream << MessCodes::error;
	_socket->flush();
	_socket->waitForBytesWritten();
	if (_socket->bytesAvailable() > 0) {
		this->readyRead();
	}
}
