#include "event.h"

#include <QTcpSocket>
#include <QDataStream>

Event::Event(QObject *parent)
{
	_id = 0;
	_founder = 0;
	_title = "";
	_desc = "";
	_date = QDateTime();
	_invited = {};
	_attending = {};
}

Event::Event(const id_type id1, const id_type id2, const QString q, const QList<id_type>&l1, const QList<id_type>&l2)
{
	 _id = id1;
	 _founder = id2;
	 _desc = q;
	 _invited = l1;
	 _attending = l2;
}

Event::Event(const Event& e): _id(e.id()), _founder(e.founder()),
										_desc(e.desc()), _date(e.date()),
										_invited(e.invited()), _attending(e.attending())
{
}

Event::Event(id_type creator, QString desc, QDateTime date, QList<id_type> inv): _id(0), _founder(creator), _desc(desc), _date(date), _invited(inv)
{

}

Event::~Event()
{

}

id_type Event::id() const
{
	return _id;
}

id_type Event::founder() const
{
	return _founder;
}

QString Event::title() const
{
	return _title;
}

QString Event::desc() const
{
	return _desc;
}

QDateTime Event::date() const
{
	return _date;
}

QList<id_type> Event::invited() const
{
	return _invited;
}

QList<id_type> Event::attending() const
{
	return _attending;
}

void Event::setId(const id_type &id)
{
	_id = id;
}

void Event::setFounder(const id_type &founder)
{
	_founder = founder;
}

void Event::setTitle(const QString &title)
{
	_title = title;
}

void Event::setDesc(const QString &desc)
{
	_desc = desc;
}

void Event::setDate(const QDateTime &date)
{
	_date = date;
}

void Event::setInvited(const QList<id_type> &invited)
{
	_invited = invited;
}

void Event::setAttending(const QList<id_type> &attending)
{
	_attending = attending;
}

void Event::operator=(const Event& e)
{
	this->_id = e.id();
	this->_founder = e.founder();
	this->_title = e.title();
	this->_desc = e.desc();
	this->_date = e.date();
	this->_invited = e.invited();
	this->_attending = e.attending();
}

QDataStream& operator<<(QDataStream& out, const Event& e)
{
	QByteArray array;
	QDataStream stream(&array, QIODevice::WriteOnly);
	stream << e._id << e._founder << e._title << e._desc << e._invited << e._attending;
	out << array;
	return out;
}

QDataStream& operator>>(QDataStream& in, Event&e)
{
	 in >> e._id >> e._founder >> e._title >> e._desc >> e._invited >> e._attending;
	 return in;
}

Event Event::readEvent(QTcpSocket *s)
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

	Event e;
	d >> e;
	return e;
}








