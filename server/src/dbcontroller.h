#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H
//select for update pamietac!
#include "event.h"
#include "user.h"

class DBController
{
public:
    DBController();
    ~DBController();

    /* User controller */
    int createUser(const User &u);
    int updateUser(const User &u);
    int removeUser(const User &u);
    User getUserById(const uid_type);
    User getUserByFbId(const uid_type);

    /* Event controller */
    int createEvent(const Event &e);
    int updateEvent(const Event &e);
    int removeEvent(const Event &e);
    Event getEvent(const eid_type);

};

#endif // DBCONTROLLER_H
