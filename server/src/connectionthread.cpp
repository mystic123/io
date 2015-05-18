#include "connectionthread.h"

#include <QHostAddress>
#include <QEventLoop>
#include <QSet>

#include "server.h"
#include "fbsync.h"

const QMap<MessCodes, ConnectionThread::mem_func> ConnectionThread::_actions = {
	{MessCodes::login, &ConnectionThread::login},
	{MessCodes::signup, &ConnectionThread::signup},
	{MessCodes::user_data, &ConnectionThread::userData},
	{MessCodes::friends_list, &ConnectionThread::friendsList},
	{MessCodes::event_data, &ConnectionThread::eventData},
	{MessCodes::create_event, &ConnectionThread::createEvent},
	{MessCodes::update_event, &ConnectionThread::updateEvent},
	{MessCodes::invite_event , &ConnectionThread::inviteEvent},
	{MessCodes::join_event, &ConnectionThread::joinEvent},
	{MessCodes::add_friend, &ConnectionThread::addFriend},
	{MessCodes::del_friend, &ConnectionThread::delFriend},
	{MessCodes::fb_friends_list, &ConnectionThread::fbFriendsList},
};

ConnectionThread::ConnectionThread(qintptr ID, QObject *parent) : QThread(parent), _socket_desc(ID), _stream(), _user(nullptr), _db(new DBController(ID))
{
}

ConnectionThread::~ConnectionThread()
{
	delete _socket;
	delete _user;
	delete _db;
}

void ConnectionThread::run()
{
	qDebug()<<"Thread started\n";

	this->setAutoDelete(false);

	_socket = new QTcpSocket();

	_stream.setDevice(_socket);

	if (!_socket->setSocketDescriptor(this->_socket_desc)) {
		emit error(_socket->error());
		return;
	}

	connect(this->_socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
	connect(this->_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

	qDebug()<<_socket_desc<<"Client connected\n";

	qDebug()<<_socket->peerName()<<" "<<_socket->peerAddress()<<" "<<_socket->peerPort()<<endl;

		exec();
}

void ConnectionThread::readyRead()
{
	qDebug() << "readyRead";
	MessCodes m_code;

	_stream >> m_code;

	if (m_code != MessCodes::error_occured)
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

void ConnectionThread::disconnected()
{
	qDebug()<<_socket_desc<<"Disconnected";
	//_socket->deleteLater();
	exit(0);
}

void ConnectionThread::login()
{
	qDebug() << "login";
	while (_socket->bytesAvailable() < sizeof(id_type)) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}
	id_type user_id;
	_stream >> user_id;
	qDebug() << "dostałem:" << user_id;
	_user = _db->getUserById(user_id);
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
		qDebug() << _user->eventsAttending() << _user->eventsInvited();
	}
	else {
		User *u = _db->getUserById(user_id);
		qDebug() << "tu" << u->eventsAttending() << u->eventsInvited();
		_stream << *u;
		delete u;
	}
	_socket->flush();
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
		_stream << u->friends();
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
	if (!e->id())
		qDebug() << "ERROR: Event id = 0";
	_stream << *e;
	_socket->flush();
	delete e;
}

void ConnectionThread::createEvent()
{
	qDebug()<<"createEvent";

	Event e = Event::readEvent(_socket);

	e.setInvited(_user->friends());
	e.setAttending({});
	_db->createEvent(e);
	id_type id = _user->id();
	delete _user;
	this->_user = _db->getUserById(id);
	sendOK();
}

void ConnectionThread::updateEvent()
{
	qDebug()<<"updateEvent";

	Event e = Event::readEvent(_socket);
	_db->updateEvent(e);

	sendOK();
}

void ConnectionThread::inviteEvent()
{
	qDebug()<<"inviteEvent";

	while (_socket->bytesAvailable() < sizeof(id_type)) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}

	id_type id;
	_stream >> id;

	Event *e = _db->getEvent(id);

	e->addInvited(_user->id());

	_db->updateEvent(*e);

	id_type uid = _user->id();
	delete _user;
	_user = _db->getUserById(uid);
	sendOK();
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

	e->addAttendant(_user->id());

	_db->updateEvent(*e);

	delete e;
	id_type uid = _user->id();
	delete _user;
	_user = _db->getUserById(uid);
	sendOK();
}

void ConnectionThread::addFriend()
{
	qDebug()<<"addFriend";

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

	id_type id;
	_stream >> id;
	this->_user->delFriend(id);
	_db->updateUser(*_user);
	id_type mid = _user->id();
	delete _user;
	_user = _db->getUserById(mid);
	sendOK();
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
	fb.fetchData();
	loop.exec();

	User u = fb.getUser();

  for (auto f : u.friends()) {
	  if (!_db->getUserById(f)->id()) {
		  u.delFriend(f);
	  }
  }

	_db->createUser(u);

	id_type id = u.id();

	_stream << u.id();
	_user = _db->getUserById(id);

	_socket->flush();
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

	QSet<id_type> user_set = QSet<id_type>::fromList(user_list);

	QSet<id_type> intersect = fb_set.intersect(user_set);

	fb_set = fb_set.subtract(intersect);

	_stream << fb_set.toList();
	_socket->flush();
}

void ConnectionThread::sendOK()
{
	_stream << MessCodes::ok;
	_socket->flush();
}