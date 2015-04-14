#include "connectionthread.h"
#include <QHostAddress>

const QMap<MessCodes, ConnectionThread::mem_func> ConnectionThread::_actions = {
	{MessCodes::user_data, &ConnectionThread::userData},
	{MessCodes::friends_list, &ConnectionThread::friendsList},
	{MessCodes::events_list, &ConnectionThread::eventsList},
	{MessCodes::event_data, &ConnectionThread::eventData},
	{MessCodes::create_event, &ConnectionThread::createEvent}
};

ConnectionThread::ConnectionThread(qintptr ID, QObject *parent) : QThread(parent), _socket_desc(ID), _user(nullptr), _db()
{
}

ConnectionThread::~ConnectionThread()
{
}

void ConnectionThread::run()
{
	qDebug()<<"Thread started\n";

	_socket = new QTcpSocket();

	if (!_socket->setSocketDescriptor(this->_socket_desc)) {
		emit error(_socket->error());
		return;
	}

	connect(this->_socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
	connect(this->_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

	qDebug()<<_socket_desc<<"Client connected\n";

	qDebug()<<_socket->peerName()<<" "<<_socket->peerAddress()<<" "<<_socket->peerPort()<<endl;

	QDataStream st(_socket);

	int retry = max_retries;

	while(_socket->bytesAvailable() < sizeof(id_type) && retry > 0) {
		_socket->waitForBytesWritten();
		retry--;
	}

	id_type user_id;

	if (_socket->bytesAvailable() >= sizeof(id_type)) {
		st >> user_id;
		_user = _db->getUserById(user_id);
		if (_user) {
			exec();
		}
		else {
			qDebug() << "error: wrong user id";
		}
	}
	else {
		qDebug() << "error connected";
	}
}

void ConnectionThread::readyRead()
{
	QByteArray code = _socket->read(sizeof(MessCodes));

	if (code.isEmpty()) {
		qDebug()<<"error\n";
		return;
	}
	qDebug()<<"code: "<<code<<endl;
	MessCodes m_code = toMessCode(code);
	if (m_code != MessCodes::error_occured)
		qDebug()<<"m_code: "<<(qint32)m_code<<endl;
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
	_socket->deleteLater();
	exit(0);
}

void ConnectionThread::userData()
{
	qDebug()<<"userData\n";
	QDataStream stream(_socket);
	id_type user_id;
	stream >> user_id;
	if (user_id == _user->id()) {
		stream << *_user;
	}
	else {
		User *u = _db->getUserById(user_id);
		stream << *u;
		u->~User();
		free(u);
	}
}

void ConnectionThread::friendsList()
{
	qDebug()<<"friendsList\n";
	QDataStream stream(_socket);
	id_type user_id;
	stream >> user_id;
	if (user_id == _user->id()) {
		stream << _user->friends();
	}
	else {
		User *u = _db->getUserById(user_id);
		stream << u->friends();
		u->~User();
		free(u);
	}
}

void ConnectionThread::eventsList()
{
	qDebug()<<"eventsList\n";
}

void ConnectionThread::eventData()
{
	qDebug()<<"eventData\n";
	QDataStream stream(_socket);
	id_type event_id;
	stream >> event_id;
	Event *e = _db->getEvent(event_id);
	stream << *e;
	e->~Event();
	free(e);
}

void ConnectionThread::createEvent()
{
	qDebug()<<"createEvent\n";
	QDataStream stream(_socket);
	Event e;
	stream >> e;
	_db->createEvent(e);
}