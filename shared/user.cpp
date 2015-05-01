#include "user.h"
#include <QTcpSocket>
#include <QDataStream>
#include <iostream>
User::User(QObject *parent)
{

}

User::User(const User &u): _id(u.id()), _friends(u.friends()),
									_eventsAttending(u.eventsAttending()),
									_eventsInvited(u.eventsInvited())
{
}

User::User(const id_type id, const QList<id_type>& f, const QList<id_type>& e1, const QList<id_type>& e2)
{
    _id = id;
    _friends = f;
    _eventsInvited = e1;
    _eventsAttending = e2;
    std::cout << id << std::endl;
    id_type i;
    foreach(i, f){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    foreach(i, e1){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    foreach(i, e2){
        std::cout << i << " ";
    }
}

User::~User()
{
}

void User::operator=(const User& u)
{
	this->_id = u.id();
	this->_friends = u._friends;
	this->_eventsAttending = u.eventsAttending();
	this->eventsInvited() = u.eventsInvited();
}

QDataStream& operator<<(QDataStream &out, const User &u)
{
	QByteArray array;
	QDataStream stream(&array, QIODevice::WriteOnly);
	stream << u._id << u._friends << u._eventsAttending << u._eventsInvited;
	out << array;
	return out;
}

QDataStream& operator>>(QDataStream &in, User &u)
{
	in >> u._id >> u._friends >> u._eventsAttending >> u._eventsInvited;
	return in;
}

User User::readUser(QTcpSocket *s)
{
	QDataStream d(s);

	while (s->bytesAvailable() < sizeof(qint32)) {
		s->waitForReadyRead(REFRESH_TIME);
	}

	qint32 size;
	d >> size;
	while (s->bytesAvailable() < size) {
		s->waitForReadyRead(REFRESH_TIME);
	}
	User u;
	d >> u;
	return u;
}
