#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QSqlDatabase>
#include "event.h"
#include "user.h"
#include "comment.h"

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
	 id_type createEvent(const Event &e);
    int updateEvent(const Event &e);
    int removeEvent(const Event &e);
    Event* getEvent(const id_type);

    /* Comment controller */
    int createComment(const Comment &c);
    int updateComment(const Comment &c);
    int removeComment(const Comment &c);
	 Comment* getComment(const id_type);


private:
    QSqlDatabase _db;
};

#endif // DBCONTROLLER_H
