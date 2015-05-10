#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QSqlDatabase>
#include "event.h"
#include "user.h"

class DBController
{
public:
    DBController(){}
    DBController(qintptr id);
    ~DBController();
    /* getter */
    QSqlDatabase db() {return this->_db;}

    /* User controller */
    int createUser(const User &u);
    int updateUser(const User &u);
    int removeUser(const User &u);
    User* getUserById(const id_type);

    /* Event controller */
    int createEvent(const Event &e);
    int updateEvent(const Event &e);
    int removeEvent(const Event &e);
    Event* getEvent(const id_type);

private:
    QSqlDatabase _db;
    void RUInside(const User &u);
    void CEInside(const Event &e, bool isUpdated);
    void REInside(const Event &e);
};

#endif // DBCONTROLLER_H
