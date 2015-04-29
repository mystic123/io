#include "event.h"

#include <QTcpSocket>
#include <QDataStream>

Event::Event(QObject *parent)
{

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

void Event::operator=(const Event& e)
{
	 this->_id = e.id();
	 this->_founder = e.founder();
	 this->_desc = e.desc();
	 this->_date = e.date();
	 this->_invited = e.invited();
	 this->_attending = e.attending();
}

QDataStream& operator<<(QDataStream& out, const Event& e)
{
	QByteArray array;
	QDataStream stream(&array, QIODevice::WriteOnly);
	stream << e._id << e._founder << e._desc << e._invited << e._attending;
	out << array;
	return out;
}

QDataStream& operator>>(QDataStream& in, Event&e)
{
	 in >> e._id >> e._founder >> e._desc >> e._invited >> e._attending;
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
