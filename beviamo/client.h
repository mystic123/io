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
     Q_INVOKABLE void getUser();

    Q_INVOKABLE void setChosenEvent(id_type id) {
        chosenEvent = id;
    }

     void setEngine(QQmlApplicationEngine *e) {
        engine = e;
     }

     Q_INVOKABLE void chosenEventModel() {
     }

     void connect();

     Q_INVOKABLE void login() {
        my_id = 12;
        this->connect();
        this->getUser();
        availableEvents = this->user->eventsInvited();

        QList<QObject*> events;

        id_type tmp = 14;
        availableEvents.append(tmp);

        for (id_type id: availableEvents) {
            events.append(this->getEvent(id));
        }

        engine->rootContext()->setContextProperty("myModel", QVariant::fromValue(events));
     }

signals:

public slots:

private:
    //QStringList<event>
    QTcpSocket *_socket;
    QDataStream _st;
    id_type my_id;
    QQmlApplicationEngine *engine;
    id_type chosenEvent;
    QList<id_type> availableEvents;
    User* user;
};

#endif // CPPCLASS_H
