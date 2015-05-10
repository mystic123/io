#include <QCoreApplication>
#include <iostream>
#include "server.h"
#include "fbsync.h"

#include "user.h"
#include "event.h"
#include "dbcontroller.h"
#include "QDebug"

void testCreateUser(){
   qDebug() << QString("createUser");
   DBController d(1415);
   for (qint16 i = 1; i<= 20; i++){
        User u;
        u.setId(i);
        u.setEmail("user" + QVariant(i).toString() + "@mail.pl");
        u.setFirstName("przed update "+ QVariant(i).toString());
        u.setLastName("drugie imie  " + QVariant(i).toString());
        u.setGender('m');
        u.setFriends({});
        u.setEventsAttending({});
        u.setEventsInvited({});
        d.createUser(u);
   }
}

void testCreateEvent(){
   qDebug() << QString("createEvent");
   DBController d(1414);
   for (qint16 i = 1; i<= 20; i++){
        Event e;
        e.setFounder(i);
        e.setTitle("Wydarzenie numer " + QVariant(i).toString());
        e.setDesc("Opis "+ QVariant(i).toString());
        e.setDate(QDateTime(QDate(2015+i,7,i+1), QTime(i,0,i)));
        e.setInvited({2});
        e.setAttending({2});
        e.setHow_long(2);
        e.setLocation("warszawa");
        d.createEvent(e);
   }
}

void testUpdateEvent(){
    qDebug() << QString("updateEvent");
    DBController d(1212);
    for(qint16 i = 1; i<= 10; i++){
        Event e;
        e.setId(i);
        e.setFounder(i);
        e.setTitle("Wydarzenie numer " + QVariant(i).toString());
        e.setDesc("Opis updated  "+ QVariant(i).toString());
        e.setDate(QDateTime(QDate(2015+i,7,i+1), QTime(i,0,i)));
        e.setInvited({});
        e.setAttending({});
        e.setHow_long(3);
        e.setLocation("warszawa");
        d.updateEvent(e);
    }
    for(qint16 i = 11; i<= 20; i++){
        Event e;
        e.setId(i);
        e.setFounder(i);
        e.setTitle("Wydarzenie numer " + QVariant(i).toString());
        e.setDesc("Opis updated "+ QVariant(i).toString());
        e.setDate(QDateTime(QDate(2015+i,7,i+1), QTime(i,0,i)));
        e.setInvited({1,3});
        e.setAttending({1});
        e.setHow_long(3);
        e.setLocation("warszawa");
        d.updateEvent(e);
    }
}

void testUpdateUser(){
    qDebug() << QString("updateUser");
    DBController d(14222);
    for(qint16 i = 1; i<= 10; i++){
        User u;
        u.setId(i);
        u.setEmail("user " + QVariant(i).toString() + "@bla.pl");
        u.setFirstName("po update  "+ QVariant(i).toString());
        u.setLastName("po update " + QVariant(i).toString());
        u.setGender('f');
        u.setFriends({1,2,3,4,5});
        u.setEventsAttending({1,2,3});
        u.setEventsInvited({1,2});
        d.updateUser(u);
    }
    for(qint16 i = 11; i<= 20; i++){
        User u;
        u.setId(i);
        u.setEmail("user " + QVariant(i).toString() + "@bla.pl");
        u.setFirstName("po update  "+ QVariant(i).toString());
        u.setLastName("drugie imie " + QVariant(i).toString());
        u.setGender('f');
        u.setFriends({});
        u.setEventsAttending({});
        u.setEventsInvited({});
        d.updateUser(u);
     }
}

void testRemoveUser(){
    DBController d(122);
    for(qint16 i = 1; i<= 20; i++){
        User u;
        u.setId(i);
        d.removeUser(u);
    }
}

void testRemoveEvent(){
    DBController d(142);
    for(qint16 i = 1; i<= 20; i++){
        Event e;
        e.setId(i);
        d.removeEvent(e);
    }
}

int main(int argc, char *argv[])
{
    /* przed uzyciem
     * wyczyscic baze danych */
    testCreateUser();
    testUpdateUser();
    testCreateEvent();
    testUpdateEvent();
}

