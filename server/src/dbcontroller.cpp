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
    /*db.setHostName("postgresql-mystic123.alwaysdata.net");
	db.setUserName("mystic123_beviamo");
	db.setPassword("beviamo");
	db.setDatabaseName("mystic123_beviamo");

    db.setHostName("localhost");
     db.setUserName("siemin93");
     db.setPassword("siemin93");
     db.setDatabaseName("bev");*/

/*to change*/

    db.setHostName("localhost");
    db.setUserName("postgres");
    db.setPassword("x");
    db.setDatabaseName("mydb");

    this->_db = db;
    this->_db.open();
}

int DBController::createUser(const User &u)
{
    if (db().isValid()){
        if (db().isOpen()){
            db().transaction();
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
				db().commit();
        } else return -1;
    } else return -1;
    return 0;
}

int DBController::updateUser(const User &u)
{
    if (db().isValid()){
        if (db().isOpen()){
            QSqlQuery query(db());
            db().transaction();
            /* protection against sql injection, update user */
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
            db().commit();
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
						  friends.push_back(query.value(0).toLongLong());

            /* adding to events and eventsAttended */
            QSqlQuery query1(db());
            query1.prepare("SELECT e_id FROM event WHERE id_founder=" + QVariant(id).toString() + ";");
            query1.exec();
            while (query1.next()){
						  events.push_back(query1.value(0).toLongLong());
						  eventsAtt.push_back(query1.value(0).toLongLong());
            }

            /* adding to eventsAttended */
            QSqlQuery query2(db());
            query2.prepare("SELECT id_event, attended FROM invited WHERE id_i_user=" + QVariant(id).toString() + ";");
            query2.exec();
            while (query2.next()){
						  events.push_back(query2.value(0).toLongLong());
                    if (query2.value(1).toBool())
								eventsAtt.push_back(query2.value(0).toLongLong());
            }

            QSqlQuery query3(db());
            query3.prepare("SELECT * FROM users WHERE u_id=" + QVariant(id).toString() + ";");
            query3.exec();

            /* making new user and setting all fields */
            User *u = new User;
            while (query3.next()){
					 u->setId(id);
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

id_type DBController::createEvent(const Event &e)
{
    if (db().isValid()){
        if (db().isOpen()){
            db().transaction();
            id_type id;
            /* protection against sql injection */
            QSqlQuery query(db());
            query.prepare("INSERT INTO event (descript, id_founder, title, location, start_date, how_long)"
                            "VALUES (?,?,?,?,?,?)"
                            "RETURNING e_id");
            query.addBindValue(QVariant(e.desc()).toString());
            query.addBindValue(QVariant(e.founder()).toString());
            query.addBindValue(QVariant(e.title()).toString());
            query.addBindValue(QVariant(e.location()).toString());
            query.addBindValue(QVariant(e.date().toString("yyyy-MM-dd hh:mm:ss")));
            query.addBindValue(QVariant(e.how_long()).toString());
            query.exec();
            while (query.next()) id = query.value(0).toLongLong();

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
            db().commit();
            return id;
        } else return -1;
    } else return -1;
}

int DBController::updateEvent(const Event &e)
{
    if (db().isValid()){
        if (db().isOpen()){
            db().transaction();
            QSqlQuery query(db());
            /* protection against sql injection, update event */
            query.prepare("UPDATE event SET descript=?, id_founder=?, title=?, location=?, start_date=?, how_long=? WHERE e_id=" + QVariant(e.id()).toString() + ";");
            query.addBindValue(QVariant(e.desc()).toString());
            query.addBindValue(QVariant(e.founder()).toString());
            query.addBindValue(QVariant(e.title()).toString());
            query.addBindValue(QVariant(e.location()).toString());
            query.addBindValue(QVariant(e.date().toString("yyyy-MM-dd hh:mm:ss")));
            query.addBindValue(QVariant(e.how_long()).toString());
            query.exec();

            QSqlQuery query2(db());
            query2.prepare("DELETE FROM invited WHERE id_event=" + QVariant(e.id()).toString() + ";");
            query2.exec();

            /* adding realations to invited */
            QSqlQuery query3(db());
            QString pre("INSERT INTO invited (id_event, id_i_user, attended) VALUES ");
            QListIterator<id_type> i(e.invited());
            bool pierwszy = true;
            while(i.hasNext()){
                if (pierwszy){
                    pre+= ("("+ QVariant(e.id()).toString() + "," + QVariant((i.peekNext())).toString() + ",");
                    if (e.attending().contains(i.next())) pre+= ("true)");
                    else pre+= ("false)");
                    pierwszy = false;
                }
                else{
                    pre+= (", ("+ QVariant(e.id()).toString() + "," + QVariant((i.peekNext())).toString() + ",");
                    if (e.attending().contains(i.next())) pre+= ("true)");
                    else pre+= ("false)");
                }
            }
            pre+=(";");
            if (!pierwszy){
                query3.prepare(pre);
                query3.exec();
            }
            db().commit();
        } else return -1;
    } else return -1;
    return 0;
}

int DBController::removeEvent(const Event &e)
{
    if (db().isValid()){
        if (db().isOpen()){
            QSqlQuery query(db());
            query.prepare("DELETE FROM event WHERE e_id=" + QVariant(e.id()).toString() + ";");
            query.exec();
        }else return -1;
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
            QList<id_type> comments;
            query2.prepare("SELECT id_i_user, attended FROM invited WHERE id_event=" + QVariant(id).toString() + ";");
            query2.exec();
            while (query2.next()){
						  invited.push_back(query2.value(0).toLongLong());
						  if (query2.value(1).toBool()) attending.push_back(query2.value(0).toLongLong());
            }

            /* making comments list from comment table */
            QSqlQuery query3(db());
            query3.prepare("SELECT c_id FROM comment WHERE id_c_event=" + QVariant(id).toString() + ";");
            query3.exec();
            while (query3.next()){
                          comments.push_back(query3.value(0).toLongLong());
            }

            /* taking rest of fields */
            QSqlQuery query(db());
            query.prepare("SELECT * FROM event WHERE e_id=" + QVariant(id).toString() + ";");
            query.exec();
            Event *e =  new Event;
            while (query.next()){
                e->setId(id);
                e->setDesc(query.value(1).toString());
                e->setFounder(query.value(2).toLongLong());
                e->setTitle(query.value(3).toString());
                e->setLocation(query.value(4).toString());
                e->setDate(QDateTime::fromString(query.value(5).toString(), "yyyy-MM-dd'T'hh:mm:ss"));
                e->setHow_long(query.value(6).toLongLong());
            }
            e->setComments(comments);
            e->setAttending(attending);
            e->setInvited(invited);
            return e;
        } else return nullptr;
    }else return nullptr;
}

int DBController::createComment(const Comment &c)
{
    if (db().isValid()){
        if (db().isOpen()){
            QSqlQuery query(db());
            /* protection against sql injection, inserting new comment */
            query.prepare("INSERT INTO comment (id_c_event, author_id, content, c_date)"
                          "VALUES (?,?,?,?)");
            query.addBindValue(QVariant(c.eventId()).toString());
            query.addBindValue(QVariant(c.authorId()).toString());
            query.addBindValue(QVariant(c.content()).toString());
            query.addBindValue(QVariant(c.date().toString("yyyy-MM-dd hh:mm:ss")));
            query.exec();

        } else return -1;
    } else return -1;
    return 0;
}

int DBController::updateComment(const Comment &c)
{
    if (db().isValid()){
        if (db().isOpen()){
            QSqlQuery query(db());
            /* protection against sql injection, update comment */
            query.prepare("UPDATE comment SET id_c_event=?, author_id=?, content=?, c_date=? WHERE c_id=" + QVariant(c.id()).toString() + ";");
            query.addBindValue(QVariant(c.eventId()).toString());
            query.addBindValue(QVariant(c.authorId()).toString());
            query.addBindValue(QVariant(c.content()).toString());
            query.addBindValue(QVariant(c.date().toString("yyyy-MM-dd hh:mm:ss")));
            query.exec();
        } else return -1;
    } else return -1;
    return 0;
}

int DBController::removeComment(const Comment &c)
{
    if (db().isValid()){
        if (db().isOpen()){
            QSqlQuery query(db());
            query.prepare("DELETE FROM comment WHERE c_id=" + QVariant(c.id()).toString() + ";");
            query.exec();
        } else return -1;
    } else return -1;
	 return 0;
}

Comment *DBController::getComment(const id_type id)
{
    if (db().isValid()){
        if (db().isOpen()){
            QSqlQuery query(db());
            query.prepare("SELECT * FROM comment WHERE c_id=" + QVariant(id).toString() + ";");
            query.exec();
            Comment *c =  new Comment;
            while (query.next()){
                c->setId(id);
                c->setEvent(query.value(1).toLongLong());
                c->setAuthorId(query.value(2).toLongLong());
                c->setContent(query.value(3).toString());
                c->setDate(QDateTime::fromString(query.value(4).toString(), "yyyy-MM-dd'T'hh:mm:ss"));
            }
            return c;
        } else return nullptr;
    }else return nullptr;
}
