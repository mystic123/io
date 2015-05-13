#include "dbcontroller.h"
#include "global.h"
#include <QtSql>
#include <QList>
#include "QDebug"
DBController::~DBController() {
    db().close();
}

DBController::DBController(qintptr id){
	QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", QString::number(id));
	db.setHostName("postgresql-mystic123.alwaysdata.net");
	db.setUserName("mystic123_beviamo");
	db.setPassword("beviamo");
	db.setDatabaseName("mystic123_beviamo");

//	db.setHostName("localhost");
//	 db.setUserName("beviamo");
//	 db.setPassword("beviamo");
//	 db.setDatabaseName("beviamo");

/*to change*/
/*
    db.setHostName("localhost");
    db.setUserName("postgres");
    db.setPassword("x");
    db.setDatabaseName("mydb");
  */
  this->_db = db;
    this->_db.open();
}

int DBController::createUser(const User &u)
{
    if (db().isValid()){
		  if (db().isOpen()){
			  qDebug() <<" jeszcze raz tutaj:";
			  qDebug() << "id:" << u.id();
			 qDebug() << "email:" << u.email();
			 qDebug() << "first name:" << u.firstName();
			 qDebug() << "last name:" << u.lastName();
			 qDebug() << "gender:" << u.gender();
				//db().transaction();
            QSqlQuery query(db());
            /* protection against sql injection, inserting new user */
            query.prepare("INSERT INTO users (u_id, email, first_name, last_name, gender)"
                          "VALUES (?,?,?,?,?)");
            query.addBindValue(QVariant(u.id()).toString());
            query.addBindValue(QVariant(u.email()).toString());
            query.addBindValue(QVariant(u.firstName()).toString());
            query.addBindValue(QVariant(u.lastName()).toString());
            query.addBindValue(QVariant(u.gender()).toString());
            query.exec();

            /* inserting into friends */
            QString pre("INSERT INTO friends (person_id,friend_id) VALUES ");
            QListIterator<id_type> i(u.friends());
            bool pierwszy = true;
            while(i.hasNext()){
                if (pierwszy){
                    pre+= ("("+ QVariant(u.id()).toString() + "," + QVariant((i.peekNext())).toString() + "), ");
                    pre+= ("("+ QVariant((i.next())).toString() + "," + QVariant(u.id()).toString() + ") ");
                    pierwszy = false;
                }
                else{
                    pre+= (", ("+ QVariant(u.id()).toString() + "," + QVariant((i.peekNext())).toString() + ") ");
                    pre+= (", ("+ QVariant((i.next())).toString() + "," + QVariant(u.id()).toString() + ") ");
                }
            }
            pre+=(";");
            if (!pierwszy){
                query.prepare(pre);
                query.exec();
            }
				//db().commit();
        } else return -1;
    } else return -1;
    return 0;
}

int DBController::updateUser(const User &u)
{
    if (db().isValid()){
        if (db().isOpen()){
            QSqlQuery query(db());
            /* protection against sql injection, inserting new user */
            query.prepare("UPDATE users SET email=?, first_name=?, last_name=?, gender=? WHERE u_id=" + QVariant(u.id()).toString() + ";");
            query.addBindValue(QVariant(u.email()).toString());
            query.addBindValue(QVariant(u.firstName()).toString());
            query.addBindValue(QVariant(u.lastName()).toString());
            query.addBindValue(QVariant(u.gender()).toString());
            query.exec();

            query.prepare("DELETE FROM friends WHERE person_id=" + QVariant(u.id()).toString() + " or friend_id=" + QVariant(u.id()).toString() + ";");
            query.exec();

            /* inserting into friends new values*/
            QString pre("INSERT INTO friends (person_id,friend_id) VALUES ");
            QListIterator<id_type> i(u.friends());
            bool pierwszy = true;
            while(i.hasNext()){
                if (pierwszy){
                    pre+= ("("+ QVariant(u.id()).toString() + "," + QVariant((i.peekNext())).toString() + "), ");
                    pre+= ("("+ QVariant((i.next())).toString() + "," + QVariant(u.id()).toString() + ") ");
                    pierwszy = false;
                }
                else{
                    pre+= (", ("+ QVariant(u.id()).toString() + "," + QVariant((i.peekNext())).toString() + ") ");
                    pre+= (", ("+ QVariant((i.next())).toString() + "," + QVariant(u.id()).toString() + ") ");
                }
            }
            pre+=(";");
            if (!pierwszy){
                query.prepare(pre);
                query.exec();
            }
         } else return -1;
    } else return -1;
    return 0;
}

int DBController::removeUser(const User &u)
{
    if (db().isValid()){
        if (db().isOpen()){
            QSqlQuery query(db());
            query.prepare("DELETE FROM users WHERE u_id=" + QVariant(u.id()).toString() + ";");
            query.exec();
        } else return -1;
    } else return -1;
    return 0;
}

User *DBController::getUserById(const id_type id)
{
    if (db().isValid()){
        if (db().isOpen()){
            QList<id_type> events, eventsAtt, friends;

            /* adding to friends */
            QSqlQuery query(db());
            query.prepare("SELECT friend_id FROM friends WHERE person_id=" + QVariant(id).toString() + ";");
            query.exec();
            while (query.next())
                    friends.push_back(query.value(0).toInt());

            /* adding to events and eventsAttended */
            QSqlQuery query1(db());
            query1.prepare("SELECT e_id FROM event WHERE id_founder=" + QVariant(id).toString() + ";");
            query1.exec();
            while (query1.next()){
                    events.push_back(query1.value(0).toInt());
                    eventsAtt.push_back(query1.value(0).toInt());
            }

            /* adding to eventsAttended */
            QSqlQuery query2(db());
            query2.prepare("SELECT id_event, attended FROM invited WHERE id_i_user=" + QVariant(id).toString() + ";");
            query2.exec();
            while (query2.next()){
                    events.push_back(query2.value(0).toInt());
                    if (query2.value(1).toBool())
                        eventsAtt.push_back(query2.value(0).toInt());
            }

            QSqlQuery query3(db());
            query3.prepare("SELECT * FROM users WHERE u_id=" + QVariant(id).toString() + ";");
            query3.exec();

            /* making new user and setting all fields */
            User *u = new User;
            while (query3.next()){
                u->setId(query3.value(0).toInt());
                u->setEmail(query3.value(1).toString());
                u->setFirstName(query3.value(2).toString());
                u->setLastName(query3.value(3).toString());
                u->setGender(QVariant(query3.value(4)).toString()[0]);
            }
            u->setFriends(friends);
            u->setEventsAttending(eventsAtt);
            u->setEventsInvited(events);
            return u;
        } else return nullptr;
    } else return nullptr;
}

int DBController::createEvent(const Event &e)
{
    if (db().isValid()){
        if (db().isOpen()){
            db().transaction();
            CEInside(e, false);
            db().commit();
        } else return -1;
    } else return -1;
    return 0;
}

int DBController::updateEvent(const Event &e)
{
    if (db().isValid()){
        if (db().isOpen()){
            db().transaction();
            REInside(e);
            CEInside(e, true);
            db().commit();
        } else return -1;
    } else return -1;
    return 0;
}

int DBController::removeEvent(const Event &e)
{
    if (db().isValid()){
        if (db().isOpen())
            REInside(e);
        else return -1;
    } else return -1;
    return 0;
}

Event *DBController::getEvent(const id_type id)
{
    if (db().isValid()){
        if (db().isOpen()){
            QSqlQuery query2(db());
            /* making invited and attending list from db table invited */
            QList<id_type> invited;
            QList<id_type> attending;
            query2.prepare("SELECT id_i_user, attended FROM invited WHERE id_event=" + QVariant(id).toString() + ";");
            query2.exec();
            while (query2.next()){
                    invited.push_back(query2.value(0).toInt());
                    if (query2.value(1).toBool()) attending.push_back(query2.value(0).toInt());
            }
            /* taking rest of fields */
            QSqlQuery query(db());
            query.prepare("SELECT * FROM event WHERE e_id=" + QVariant(id).toString() + ";");
            query.exec();
            Event *e =  new Event;
            while (query.next()){
                e->setId(query.value(0).toInt());
                e->setDesc(query.value(1).toString());
                e->setFounder(query.value(2).toInt());
                e->setTitle(query.value(3).toString());
                e->setLocation(query.value(4).toString());
                e->setDate(QDateTime::fromString(query.value(5).toString(), "yyyy-MM-dd'T'hh:mm:ss"));
                e->setHow_long(query.value(6).toInt());
            }
            e->setAttending(attending);
            e->setInvited(invited);
            return e;
        } else return nullptr;
    }else return nullptr;
}

/* private */

void DBController::CEInside(const Event &e, bool isUpdated)
{
    id_type id;
    /* protection against sql injection */

    QSqlQuery query(db());
    if (isUpdated){
        query.prepare("INSERT INTO event (e_id, descript, id_founder, title, location, start_date, how_long)"
                    "VALUES (?,?,?,?,?,?,?)");
        query.addBindValue(QVariant(e.id()).toString());
    }
    else {
        query.prepare("INSERT INTO event (descript, id_founder, title, location, start_date, how_long)"
                    "VALUES (?,?,?,?,?,?)"
                    "RETURNING e_id");
    }
    query.addBindValue(QVariant(e.desc()).toString());
    query.addBindValue(QVariant(e.founder()).toString());
    query.addBindValue(QVariant(e.title()).toString());
    query.addBindValue(QVariant(e.location()).toString());
    query.addBindValue(QVariant(e.date().toString("yyyy-MM-dd hh:mm:ss")));
    query.addBindValue(QVariant(e.how_long()).toString());
    query.exec();

    if (!isUpdated)
        while (query.next()) id = query.value(0).toInt();
    else
        id = e.id();

    /* adding realations to invited */

    QString pre("INSERT INTO invited (id_event, id_i_user, attended) VALUES ");
    QListIterator<id_type> i(e.invited());
    bool pierwszy = true;
    while(i.hasNext()){
        if (pierwszy){
            pre+= ("("+ QVariant(id).toString() + "," + QVariant((i.peekNext())).toString() + ",");
            if (e.attending().contains(i.next())) pre+= ("true)");
            else pre+= ("false)");
            pierwszy = false;
        }
        else{
            pre+= (", ("+ QVariant(id).toString() + "," + QVariant((i.peekNext())).toString() + ",");
            if (e.attending().contains(i.next())) pre+= ("true)");
            else pre+= ("false)");
        }
    }
    pre+=(";");
    if (!pierwszy){
        query.prepare(pre);
        query.exec();
    }
    if(query.isActive()) query.clear();
}

void DBController::REInside(const Event &e)
{
    QSqlQuery query(db());
    query.prepare("DELETE FROM event WHERE e_id=" + QVariant(e.id()).toString() + ";");
    query.exec();
}
