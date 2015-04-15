#ifndef EVENT_H
#define EVENT_H

#include "global.h"
#include "serializationexception.h"

class Event
{
public:
	explicit Event(id_type);
	Event();
    explicit Event(const id_type, const id_type, const QString,const QList<id_type>&, const QList<id_type>&);
//	explicit Event(QByteArray) throw(SerializationException&);
   virtual ~Event();
	id_type id() const { return _id; }
	QString desc() const { return _desc; }
    id_type creator() const { return _creator; }
	QList<id_type> invited() const { return QList<id_type>(_invited); }
	QList<id_type> attending() const { return QList<id_type>(_attending); }

//   operator QByteArray const();

	friend QDataStream& operator<<(QDataStream&, const Event&);
	friend QDataStream& operator>>(QDataStream&, Event&);

private:
	id_type _id;
	id_type _creator;
   QString _desc;
	QList<id_type> _invited;
	QList<id_type> _attending;
   /* Location */
   /* Comments */

	/* forbidden */
	Event(const Event&);

};

#endif // EVENT_H
