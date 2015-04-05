#include "event.h"

Event::Event(eid_type id): _id(id)
{

}

Event::Event(QByteArray) throw(SerializationException&)
{

}

Event::~Event()
{

}

Event::operator const QByteArray()
{
	return QByteArray();
}
