#ifndef USER_H
#define USER_H

#include <QList>
#include "global.h"
#include "serializationexception.h"

class User
{
public:
	User();
	explicit User(const id_type, const QList<id_type>&);
	//explicit User(QDataStream&) throw(SerializationException&);
   virtual ~User();
	id_type id() const { return _id; }
	QList<id_type> friends() const { return _friends; }
	QList<id_type> eventsAttending() const { return _eventsAttending; }
	QList<id_type> eventsInvited() const { return _eventsInvited; }

	/* serialization */
	friend QDataStream& operator<<(QDataStream&, const User&);
	friend QDataStream& operator>>(QDataStream&, User&);

private:
	id_type _id;
	QList<id_type> _friends;
	QList<id_type> _eventsAttending;
	QList<id_type> _eventsInvited;

    //nothing
	/* forbidden */
	User(const User&);

};

#endif // USER_H
