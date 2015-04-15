#include "event.h"

Event::Event(id_type id): _id(id)
{

}
Event::Event(const id_type id1, const id_type id2, const QString q, const QList<id_type>&l1, const QList<id_type>&l2)
{
    _id = id1;
    _creator = id2;
    _desc = q;
    _invited = l1;
    _attending = l2;
}

//Event::Event(QByteArray) throw(SerializationException&)
//{

//}

Event::Event()
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
    out << e._id << e._creator << e._desc << e._invited << e._attending;
	return out;
}

QDataStream& operator>>(QDataStream& in, Event&e)
{
	e = Event();
    in >> e._id >> e._creator >> e._desc >> e._invited >> e._attending;
	return in;
}
