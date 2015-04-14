#include "connectionthread.h"
#include <QHostAddress>

const QMap<MessCodes, ConnectionThread::mem_func> ConnectionThread::_actions = {
	{MessCodes::user_data, &ConnectionThread::userData},
	{MessCodes::friends_list, &ConnectionThread::friendsList},
	{MessCodes::events_list, &ConnectionThread::eventsList},
	{MessCodes::event_data, &ConnectionThread::eventData},
	{MessCodes::create_event, &ConnectionThread::createEvent}
};

ConnectionThread::ConnectionThread(qintptr ID, QObject *parent) : QThread(parent), _socket_desc(ID), _user(nullptr)
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

	exec();
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
	uid_type user_id;
	stream >> user_id;
	QList<uid_type> l;
	l.push_back(74567);
	l.push_back(24141);
	l.push_back(1423145);
	User u(12345, l);
	stream << u;
}

void ConnectionThread::friendsList()
{
	qDebug()<<"friendsList\n";
}

void ConnectionThread::eventsList()
{
	qDebug()<<"eventsList\n";
}

void ConnectionThread::eventData()
{
	qDebug()<<"eventData\n";
}

void ConnectionThread::createEvent()
{
	qDebug()<<"createEvent\n";
	QDataStream stream(_socket);
	uid_type creator;
	QString desc;
	QDateTime date;
	QList<uid_type> _invited;
	stream >> creator >> desc >> date >> _invited;
}