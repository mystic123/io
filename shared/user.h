#ifndef USER_H
#define USER_H

#include "global.h"

class QTcpSocket;

class User : public QObject
{
	Q_OBJECT

public:
	explicit User(QObject *parent =0);
    explicit User(const id_type, const QList<id_type>&, const QList<id_type>&, const QList<id_type>&);
	User(const User&);

   virtual ~User();
	id_type id() const { return _id; }
	QList<id_type> friends() const { return _friends; }
    QList<id_type> eventsAttending() const { return _eventsAttending; }
	QList<id_type> eventsInvited() const { return _eventsInvited; }

	/* opertators */
	void operator=(const User&);

	/* serialization */
	friend QDataStream& operator<<(QDataStream&, const User&);
	friend QDataStream& operator>>(QDataStream&, User&);

	/* static functions */
	static User readUser(QTcpSocket*);

private:
	id_type _id;
	QList<id_type> _friends;
	QList<id_type> _eventsAttending;
	QList<id_type> _eventsInvited;

};

#endif // USER_H
