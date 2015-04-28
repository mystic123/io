#include "event.h"

#include <QTcpSocket>
#include <QDataStream>

Event::Event(id_type id): _id(id)
{

}

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

//Event::Event(QByteArray) throw(SerializationException&)
//{

//}

Event::Event(const Event& e) {
	 this->_id = e.id();
	 this->_founder = e.founder();
	 this->_desc = e.desc();
	 this->_date = e.date();
	 this->_invited = e.invited();
	 this->_attending = e.attending();
}

void Event::operator=(const Event& e) {
	 this->_id = e.id();
	 this->_founder = e.founder();
	 this->_desc = e.desc();
	 this->_date = e.date();
	 this->_invited = e.invited();
	 this->_attending = e.attending();
}

Event::Event(id_type creator, QString desc, QDateTime date, QList<id_type> inv): _id(0), _founder(creator), _desc(desc), _date(date), _invited(inv)
{

}

Event::~Event()
{

}

Event Event::readEvent(QTcpSocket *s)
{
	QDataStream d(s);
	while (s->bytesAvailable() < sizeof(qint32)) {
		s->waitForReadyRead(100);
	}

	//qint32 size;
	qDebug() << s->bytesAvailable();
	//d >> size;
	//qDebug() << "mam inta" << size;
	/*while (s->bytesAvailable() < size) {
		qDebug() << s->bytesAvailable();
		s->waitForReadyRead(100);
	}*/
	Event e;
	d >> e;
	return e;
}

QDataStream& operator<<(QDataStream& out, const Event& e)
{
	QByteArray array;
	QDataStream stream(&array, QIODevice::WriteOnly);
	stream << e.id() << e.founder() << e.desc() << e.invited() << e.attending();
	qint32 size = sizeof(array);
	 out << array;
	 qDebug() << "sizeof:" << size;
	return out;
}

QDataStream& operator>>(QDataStream& in, Event&e)
{
	 in >> e._id >> e._founder >> e._desc >> e._invited >> e._attending;
	 return in;
}
