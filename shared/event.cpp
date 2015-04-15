#include "event.h"

Event::Event(id_type id): _id(id)
{

}

//Event::Event(QByteArray) throw(SerializationException&)
//{

//}

Event::Event()
{

}

Event::Event(id_type creator, QString desc, QDateTime date, QList<id_type> inv): _id(0), _creator(creator), _desc(desc), _date(date), _invited(inv)
{

}

Event::~Event()
{

}

//Event::operator const QByteArray()
//{
//	return QByteArray();
//}

QDataStream& operator<<(QDataStream& out, const Event& e)
{
	out << e._id << e._creator << e._desc << e._date << e._invited << e._attending;
	return out;
}

QDataStream& operator>>(QDataStream& in, Event&e)
{
	e = Event();
	in >> e._id >> e._creator >> e._desc >> e._date >> e._invited >> e._attending;
	return in;
}
