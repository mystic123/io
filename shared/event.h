#ifndef EVENT_H
#define EVENT_H

#include "global.h"
#include "serializationexception.h"

class QTcpSocket;

class Event : public QObject
{
	Q_OBJECT

public:
	explicit Event(id_type);
	explicit Event(QObject *parent = 0);
	explicit Event(const id_type, const id_type, const QString,const QList<id_type>&, const QList<id_type>&);
	void operator=(const Event& e);
	Event(const Event& e);
	//	explicit Event(QByteArray) throw(SerializationException&);
	Event(id_type, QString, QDateTime, QList<id_type>);
	virtual ~Event();
	id_type id() const { return _id; }
	QString desc() const { return _desc; }
	QDateTime date() const { return _date; }
	id_type founder() const { return _founder; }
	QList<id_type> invited() const { return QList<id_type>(_invited); }
	QList<id_type> attending() const { return QList<id_type>(_attending); }

	/* serialization */
	friend QDataStream& operator<<(QDataStream&, const Event&);
	friend QDataStream& operator>>(QDataStream&, Event&);

	/* static funcitons */
	static Event readEvent(QTcpSocket*);

private:
	id_type _id;
	id_type _founder;
	QString _desc;
	QDateTime _date;
	QList<id_type> _invited;
	QList<id_type> _attending;
	/* Location */
	/* Comments */

};

#endif // EVENT_H
