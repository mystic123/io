#include "connectionthread.h"
#include <QHostAddress>

const QMap<MessCodes, ConnectionThread::mem_func> ConnectionThread::_actions = {
	{MessCodes::login, &ConnectionThread::login},
	{MessCodes::user_data, &ConnectionThread::userData},
	{MessCodes::friends_list, &ConnectionThread::friendsList},
	{MessCodes::events_list, &ConnectionThread::eventsList},
	{MessCodes::event_data, &ConnectionThread::eventData},
	{MessCodes::create_event, &ConnectionThread::createEvent},
	{MessCodes::update_event, &ConnectionThread::updateEvent},
	{MessCodes::invite_event , &ConnectionThread::inviteEvent},
	{MessCodes::join_event , &ConnectionThread::joinEvent},
	{MessCodes::add_friend , &ConnectionThread::addFriend},
	{MessCodes::del_friend , &ConnectionThread::delFriend}
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
	if (_socket->bytesAvailable() > 0) {
		this->readyRead();
	}
}

void ConnectionThread::userData()
{
	qDebug()<<"userData\n";

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
		_stream << *u;
		delete u;
	}
	_socket->flush();
	if (_socket->bytesAvailable() > 0) {
		this->readyRead();
	}
}

void ConnectionThread::friendsList()
{
	qDebug()<<"friendsList\n";

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
	if (_socket->bytesAvailable() > 0) {
		this->readyRead();
	}
}

void ConnectionThread::eventsList()
{
	qDebug()<<"eventsList\n";

	_socket->waitForReadyRead();

}

void ConnectionThread::eventData()
{
	qDebug()<<"eventData\n";

	while (_socket->bytesAvailable() < sizeof(id_type)) {
		_socket->waitForReadyRead(REFRESH_TIME);
	}

	id_type event_id;
	_stream >> event_id;
	Event *e = _db->getEvent(event_id);

	_stream << *e;
	_socket->flush();
	delete e;
	if (_socket->bytesAvailable() > 0) {
		this->readyRead();
	}
}

void ConnectionThread::createEvent()
{
	qDebug()<<"createEvent\n";

	_socket->waitForReadyRead();

	Event e;
	_stream >> e;
	_db->createEvent(e);
}

void ConnectionThread::updateEvent()
{
	qDebug()<<"updateEvent\n";

	_socket->waitForReadyRead();

	Event e;
	_stream >> e;
	_db->updateEvent(e);
}

void ConnectionThread::inviteEvent()
{
	qDebug()<<"inviteEvent\n";

	_socket->waitForReadyRead();

	QList<id_type> list;
	_stream >> list;

}

void ConnectionThread::joinEvent()
{
	qDebug()<<"joinEvent\n";
}

void ConnectionThread::addFriend()
{
	qDebug()<<"addFriend\n";
}

void ConnectionThread::delFriend()
{
	qDebug()<<"delFriend\n";
}