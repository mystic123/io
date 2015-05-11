#ifndef CPPCLASS_H
#define CPPCLASS_H

#include <QObject>
#include <QQuickItem>
#include <QQuickTextDocument>
#include <QTextDocument>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QVariant>
#include <QQmlContext>

#include "event.h"
#include "global.h"
#include "user.h"
#include <QQmlApplicationEngine>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();

     Q_INVOKABLE Event* getEvent(id_type id);
     Q_INVOKABLE User* getUser(id_type id);

     void setEngine(QQmlApplicationEngine *e) {
        engine = e;
     }

//     QList<QString> id_to_name(Event e) {
//        QList<QString> r;
//        for (id_type id: e.attending()) {
//            r.append(getUser(id)->NICK);
//        }
//     }

     Q_INVOKABLE void chosenEventModel(qint32 id) {
         id_type id_tmp = id;
         chosenEvent = *getEvent(id_tmp);
     }

     Q_INVOKABLE QString eventDesc() {
         return chosenEvent.desc();
     }

     Q_INVOKABLE void addEvent(QString desc) {
		  Event e;//(my_id, desc);
		  e.setDesc(desc);
		  e.setFounder(my_id);
        _st << MessCodes::create_event;
        _st << e;
        _socket->flush();
        _socket->waitForBytesWritten();
        this->getUser(my_id);
        qDebug() << user->eventsInvited();

        availableEvents = user->eventsInvited();

        QList<QObject*> events;

        for (id_type id: availableEvents) {
            events.append(this->getEvent(id));
        }

        engine->rootContext()->setContextProperty("eventsList", QVariant::fromValue(events));
     }

     void connect();

     Q_INVOKABLE void login() {
        my_id = 5;
        this->connect();
        this->getUser(my_id);
        availableEvents = user->eventsInvited();

        QList<QObject*> events;

        for (id_type id: availableEvents) {
            events.append(this->getEvent(id));
        }

        engine->rootContext()->setContextProperty("eventsList", QVariant::fromValue(events));
     }

signals:

public slots:

private:
    //QStringList<event>
    QTcpSocket *_socket;
    QDataStream _st;
    id_type my_id;
    QQmlApplicationEngine *engine;
    QList<id_type> availableEvents;
    User* user;
    Event chosenEvent;

};

#endif // CPPCLASS_H
