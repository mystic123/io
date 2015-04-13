#ifndef USER_H
#define USER_H

#include <QList>
#include "global.h"
#include "serializationexception.h"

class User
{
public:
	explicit User(const uid_type);
	explicit User(QByteArray&) throw(SerializationException&);
   virtual ~User();
	uid_type id() const { return _id; }
	QList<uid_type> friends() const { return _friends; }

   operator QByteArray const();

private:
	uid_type _id;
	QList<uid_type> _friends;
    //nothing
	/* forbidden */
	User(const User&);

};

#endif // USER_H
