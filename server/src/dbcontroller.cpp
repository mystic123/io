#include "dbcontroller.h"
#include "global.h"
#include <QtSql>
#include <QList>

DBController::DBController() {}
DBController::~DBController() {}

int DBController::createUser(const User &u)
{
    QSqlDatabase db = makeConnection();

    if (db.isValid()){
        db.open();
        if (db.isOpen()){
            db.transaction();
            CUInside(u, db);
            db.commit();
        } else return -1;
    } else return -1;
    return 0;
}

int DBController::updateUser(const User &u)
{
    QSqlDatabase db = makeConnection();
    if (db.isValid()){
        db.open();
        if (db.isOpen()){
            db.transaction();
            RUInside(u, db);
            CUInside(u, db);
            db.commit();
        } else return -1;
    } else return -1;
    return 0;
}

int DBController::removeUser(const User &u)
{
    QSqlDatabase db = makeConnection();
    if (db.isValid()){
        db.open();
        if (db.isOpen())
            RUInside(u, db);
        else return -1;
    } else return -1;
    return 0;
}

User *DBController::getUserById(const id_type id)
{
    QSqlDatabase db = makeConnection();
    if (db.isValid()){
        db.open();
        if (db.isOpen()){
            QSqlQuery query(db);
            query.prepare("SELECT friend_id FROM friends WHERE person_id=" + QVariant(id).toString() + ";");
				query.exec();
            QList<id_type> friends;
            while (query.next())
                    friends.push_back(query.value(0).toInt());
            User *r = new User(id, friends);
            return r;
        } else return nullptr;
    }else return nullptr;
}

int DBController::createEvent(const Event &e)
{
    QSqlDatabase db = makeConnection();

    if (db.isValid()){
        db.open();
        if (db.isOpen()){
            db.transaction();
            CEInside(e, db);
            db.commit();
        } else return -1;
    } else return -1;
    return 0;
return 0;
}

int DBController::updateEvent(const Event &e)
{
    QSqlDatabase db = makeConnection();
    if (db.isValid()){
        db.open();
        if (db.isOpen()){
            db.transaction();
            REInside(e, db);
            CEInside(e, db);
            db.commit();
        } else return -1;
    } else return -1;
    return 0;
return 0;
}

int DBController::removeEvent(const Event &e)
{
    QSqlDatabase db = makeConnection();
    if (db.isValid()){
        db.open();
        if (db.isOpen())
            REInside(e, db);
        else return -1;
    } else return -1;
    return 0;
return 0;
}

Event *DBController::getEvent(const id_type id)
{
    QSqlDatabase db = makeConnection();
    if (db.isValid()){
        db.open();
        if (db.isOpen()){
            QSqlQuery query(db);
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

QSqlDatabase DBController::makeConnection()
{
qDebug() << "make conn start";
	 QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", QString::number(_id));
	 //added unique (i hope so) id
	 db.setHostName("postgresql-mystic123.alwaysdata.net");
	 db.setUserName("mystic123_beviamo");
	 db.setPassword("beviamo");
	 db.setDatabaseName("mystic123_beviamo");
	 //db.setHostName("localhost");
	 //db.setUserName("beviamo");
	 //db.setPassword("beviamo");
	 //db.setDatabaseName("beviamo");
	 qDebug() << "make conn end";
    return db;
}

void DBController::CUInside(const User &u, QSqlDatabase db)
{
    QSqlQuery query(db);
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

void DBController::RUInside(const User &u, QSqlDatabase db)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM users WHERE u_id=" + QVariant(u.id()).toString() + ";");
    query.exec();
}

void DBController::CEInside(const Event &e, QSqlDatabase db)
{
    QSqlQuery query(db);
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

void DBController::REInside(const Event &e, QSqlDatabase db)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM event WHERE e_id=" + QVariant(e.id()).toString() + ";");
    query.exec();
}
