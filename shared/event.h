#ifndef EVENT_H
#define EVENT_H

#include "global.h"
#include "serializationexception.h"

class Event
{
public:
	explicit Event(eid_type);
	Event();
//	explicit Event(QByteArray) throw(SerializationException&);
   virtual ~Event();
	eid_type id() const { return _id; }
	QDateTime date() const { return _date; }
	QString desc() const { return _desc; }
	QList<uid_type> invited() const { return QList<uid_type>(_invited); }
	QList<uid_type> attending() const { return QList<uid_type>(_attending); }

//   operator QByteArray const();

	friend QDataStream& operator<<(QDataStream&, const Event&);
	friend QDataStream& operator>>(QDataStream&, Event&);

private:
	eid_type _id;
	uid_type _creator;
   QString _desc;
   QDateTime _date;
	QList<uid_type> _invited;
	QList<uid_type> _attending;
   /* Location */
   /* Comments */

	/* forbidden */
	Event(const Event&);

};
/*
 *
 * -id:int
-description: string
-time: (time_type)
-place: Location
-invited: List<User>
-attending: List<User>
-comments: List<Comments>
 */
#endif // EVENT_H
