#ifndef EVENT_H
#define EVENT_H

#include "global.h"
#include <QObject>
#include <QMetaType>

class QTcpSocket;

class Event : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString desc READ desc)
    Q_PROPERTY(QString event_id READ id)

public:
	explicit Event(QObject *parent = 0);
	explicit Event(const id_type, const id_type, const QString,const QList<id_type>&, const QList<id_type>&);
	Event(const Event&);

	Event(id_type, QString, QDateTime, QList<id_type>);
	virtual ~Event();

	/* getters */
	id_type id() const;
	id_type founder() const;
	QString title() const;
	QString desc() const;
	QDateTime date() const;
	QList<id_type> invited() const;
	QList<id_type> attending() const;

	/* setters */
	void setId(const id_type &id);
	void setFounder(const id_type &founder);
	void setTitle(const QString &title);
	void setDesc(const QString &desc);
	void setDate(const QDateTime &date);
	void setInvited(const QList<id_type> &invited);
	void setAttending(const QList<id_type> &attending);

	/* opertators */
	void operator=(const Event&);

	/* serialization */
	friend QDataStream& operator<<(QDataStream&, const Event&);
	friend QDataStream& operator>>(QDataStream&, Event&);

	/* static funcitons */
	static Event readEvent(QTcpSocket*);

private:
	id_type _id;
	id_type _founder;
	QString _title;
	QString _desc;
	QDateTime _date;
	QList<id_type> _invited;
	QList<id_type> _attending;
	/* Location */
	/* Comments */
};

Q_DECLARE_METATYPE(Event)
#endif // EVENT_H
