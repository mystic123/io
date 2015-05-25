#ifndef EVENT_H
#define EVENT_H

#include "global.h"
#include <QObject>
#include <QMetaType>

class QTcpSocket;

class Event : public QObject
{
    Q_OBJECT
	 Q_PROPERTY(QString desc READ desc CONSTANT)
	 Q_PROPERTY(QString loc READ location CONSTANT)
	 Q_PROPERTY(QString title READ title CONSTANT)
	 Q_PROPERTY(qint32 event_id READ id)

public:
	explicit Event(QObject *parent = 0);
	explicit Event(const id_type, const id_type, const QString,const QList<id_type>&, const QList<id_type>&);
	Event(const Event&);
    //Event(){}
	Event(id_type, QString, QDateTime, QList<id_type>);
	virtual ~Event();

	/* getters */
	id_type id() const;
	id_type founder() const;
	QString title() const;
	QString desc() const;
	QString location() const;
	QDateTime date() const;
	qint64 how_long() const;
    QList<id_type> comments() const;
	QList<id_type> invited() const;
	QList<id_type> attending() const;

	/* setters */
	void setId(const id_type &id);
	void setFounder(const id_type &founder);
	void setTitle(const QString &title);
	void setDesc(const QString &desc);
	void setLocation(const QString &location);
	void setDate(const QDateTime &date);
	void setHow_long(const qint64 &how_long);
    void setComments(const QList<id_type> &comments);
	void setInvited(const QList<id_type> &invited);
	void setAttending(const QList<id_type> &attending);

	void addAttendant(id_type);
	void addInvited(id_type);
	void addComment(id_type);
	void delComment(id_type);

	/* opertators */
	void operator=(const Event&);
	bool operator==(const Event&) const;

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
    QString _location;
	QDateTime _date;
	 qint64 _how_long;
    QList<id_type> _comments;
	QList<id_type> _invited;
	QList<id_type> _attending;
	/* Location */
};

Q_DECLARE_METATYPE(Event)
#endif // EVENT_H
