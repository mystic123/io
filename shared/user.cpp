#include "user.h"
#include <QTcpSocket>
#include <QDataStream>
#include <iostream>

User::User(QObject *parent)
{
	_id = 0;
	_email = "";
	_firstName = "";
	_lastName = "";
	_gender = 'u';
	_friends = QList<id_type>();
	_eventsAttending = QList<id_type>();
	_eventsInvited = QList<id_type>();
}


User::User(const User &u)
{
	this->_id = u.id();
	this->_email = u.email();
	this->_firstName = u.firstName();
	this->_lastName = u.lastName();
	this->_gender = u.gender();
	this->_friends = u.friends();
	this->_eventsAttending = u.eventsAttending();
	this->_eventsInvited = u.eventsInvited();
}

User::User(const id_type id, const QList<id_type>& f, const QList<id_type>& e1, const QList<id_type>& e2)
{
    _id = id;
    _friends = f;
    _eventsInvited = e1;
    _eventsAttending = e2;
}

User::~User()
{
}

id_type User::id() const
{
	return _id;
}

QString User::email() const
{
	return _email;
}

QString User::firstName() const
{
	return _firstName;
}

QString User::lastName() const
{
	return _lastName;
}

QString User::name() const
{
	return _firstName + " " + _lastName;
}

QChar User::gender() const
{
	return _gender;
}

QList<id_type> User::friends() const
{
	return _friends;
}

QList<id_type> User::eventsAttending() const
{
	return _eventsAttending;
}

QList<id_type> User::eventsInvited() const
{
	return _eventsInvited;
}

void User::setId(const id_type &id)
{
	_id = id;
}

void User::setEmail(const QString &email)
{
	_email = email;
}

void User::setFirstName(const QString &firstName)
{
	_firstName = firstName;
}

void User::setLastName(const QString &lastName)
{
	_lastName = lastName;
}

void User::setGender(const QChar &gender)
{
	static QList<QChar> genders = {'f', 'm', 'o', 'u'};
	if (genders.contains(gender))
		_gender = gender;
	else {
		qDebug() << "WARNING: Wrong gender symbol. Allowed are:" << genders;
		_gender = 'u';
    }
}

void User::setFriends(const QList<id_type> &friends)
{
	_friends = friends;
}

void User::setEventsAttending(const QList<id_type> &eventsAttending)
{
	_eventsAttending = eventsAttending;
}

void User::setEventsInvited(const QList<id_type> &eventsInvited)
{
	_eventsInvited = eventsInvited;
}

void User::addFriend(id_type id)
{
	_friends.append(id);
}

void User::addFriend(const QList<id_type>& l)
{
	_friends.append(l);
}

void User::delFriend(id_type id)
{
	if (_friends.contains(id)) {
		auto it = _friends.begin();
		while (*it != id)
			it++;
		_friends.erase(it);
	}
}

void User::delFriend(const QList<id_type>& l)
{
	for (auto x : l) {
		delFriend(x);
	}
}

void User::inviteToEvent(id_type id)
{
	if (!_eventsAttending.contains(id))
		_eventsInvited.append(id);
}

void User::joinEvent(id_type id)
{
	if (!_eventsAttending.contains(id))
		_eventsAttending.append(id);
}


void User::operator=(const User& u)
{
	this->_id = u.id();
	this->_email = u.email();
	this->_firstName = u.firstName();
	this->_lastName = u.lastName();
	this->_gender = u.gender();
	this->_friends = u.friends();
	this->_eventsAttending = u.eventsAttending();
	this->_eventsInvited = u.eventsInvited();
}

QDataStream& operator<<(QDataStream &out, const User &u)
{
	QByteArray array;
	QDataStream stream(&array, QIODevice::WriteOnly);
    stream << u._id << u._email << u._firstName << u._lastName << u._gender << u._friends << u._eventsAttending << u._eventsInvited;
	out << array;
	return out;
}

QDataStream& operator>>(QDataStream &in, User &u)
{
    in >> u._id >> u._email >> u._firstName >> u._lastName >> u._gender >> u._friends >> u._eventsAttending >> u._eventsInvited;
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


