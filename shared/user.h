#ifndef USER_H
#define USER_H

#include <QList>
#include "global.h"

class User
{
public:
   explicit User(uid_type id);
   virtual ~User();
   uid_type id() const;
   QList<id_type> friends() const;

private:
   const uid_type _id;
   QList<id_type> *_friends;
};

#endif // USER_H
