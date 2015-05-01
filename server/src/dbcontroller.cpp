#include "dbcontroller.h"
#include "global.h"
#include <QtSql>
#include <QList>

DBController::~DBController() {
    db().close();
}

DBController::DBController(qintptr id){
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", QString::number(id));
    db.setHostName("postgresql-mystic123.alwaysdata.net");
    db.setUserName("mystic123_beviamo");
    db.setPassword("beviamo");
    db.setDatabaseName("mystic123_beviamo");
    this->_db = db;
    this->_db.open();
}

int DBController::createUser(const User &u)
{
    if (db().isValid()){
        if (db().isOpen()){
            db().transaction();
            CUInside(u);
            db().commit();
        } else return -1;
    } else return -1;
    return 0;
}

int DBController::updateUser(const User &u)
{
    if (db().isValid()){
        if (db().isOpen()){
            db().transaction();
            RUInside(u);
            CUInside(u);
            db().commit();
        } else return -1;
    } else return -1;
    return 0;
}

int DBController::removeUser(const User &u)
{
    if (db().isValid()){
        if (db().isOpen())
            RUInside(u);
        else return -1;
    } else return -1;
    return 0;
}

User *DBController::getUserById(const id_type id)
{
    if (db().isValid()){
        if (db().isOpen()){
            QList<id_type> events;
            QList<id_type> eventsAtt;
            QList<id_type> friends;
            QSqlQuery query(db());

            query.prepare("SELECT friend_id FROM friends WHERE person_id=" + QVariant(id).toString() + ";");
            query.exec();
            while (query.next())
                    friends.push_back(query.value(0).toInt());

            QSqlQuery query1(db());
            query1.prepare("SELECT e_id FROM event WHERE id_founder=" + QVariant(id).toString() + ";");
            query1.exec();
            while (query1.next()){
                    events.push_back(query1.value(0).toInt());
                    eventsAtt.push_back(query1.value(0).toInt());
            }

            QSqlQuery query2(db());
            query2.prepare("SELECT id_event, attended FROM invited WHERE id_i_user=" + QVariant(id).toString() + ";");
            query2.exec();
            while (query2.next()){
                    events.push_back(query2.value(0).toInt());
                    if (query2.value(1).toBool())
                        eventsAtt.push_back(query2.value(0).toInt());
            }

            User *r = new User(id, friends, events, eventsAtt);
            return r;
        } else return nullptr;
    }else return nullptr;
}

int DBController::createEvent(const Event &e)
{
    if (db().isValid()){
        if (db().isOpen()){
            db().transaction();
            CEInside(e);
            db().commit();
        } else return -1;
    } else return -1;
    return 0;
return 0;
}

int DBController::updateEvent(const Event &e)
{
    if (db().isValid()){
        if (db().isOpen()){
            db().transaction();
            REInside(e);
            CEInside(e);
            db().commit();
        } else return -1;
    } else return -1;
    return 0;
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
return 0;
}

Event *DBController::getEvent(const id_type id)
{
    if (db().isValid()){
        if (db().isOpen()){
            QSqlQuery query(db());
            query.prepare("SELECT descript, id_founder FROM event WHERE e_id=" + QVariant(id).toString() + ";");
            query.exec();
            id_type _creator;
            QString _desc;
            QList<id_type> invited;
            QList<id_type> attending;
            while (query.next()) {
                     _desc = QString(query.value(0).toString());
                     _creator = query.value(1).toInt();
            }
            query.prepare("SELECT id_i_user, attended FROM invited WHERE id_event=" + QVariant(id).toString() + ";");
            query.exec();
            while (query.next()){
                    invited.push_back(query.value(0).toInt());
                    if (query.value(1).toBool()) attending.push_back(query.value(0).toInt());
            }
            Event *r = new Event(id, _creator, _desc, invited, attending);
            return r;
        } else return nullptr;
    }else return nullptr;
}

/* private */
void DBController::CUInside(const User &u)
{
    QSqlQuery query(db());
    query.prepare("INSERT INTO users VALUES(" + QVariant(u.id()).toString() + ");");
    query.exec();
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
    if(!pierwszy) {
        query.prepare(pre);
        query.exec();
    }
    if(query.isActive()) query.clear();
}

void DBController::RUInside(const User &u)
{
    QSqlQuery query(db());
    query.prepare("DELETE FROM users WHERE u_id=" + QVariant(u.id()).toString() + ";");
    query.exec();
}

void DBController::CEInside(const Event &e)
{
    QSqlQuery query(db());
    query.prepare("INSERT INTO event VALUES(" + QVariant(e.id()).toString() +
						", " + "'" + QVariant(e.desc()).toString() + "'"+ ", " + QVariant(e.founder()).toString()+");");
    query.exec();
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
    if(!pierwszy) {
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
