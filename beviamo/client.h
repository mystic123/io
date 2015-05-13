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
#include <QUrl>
#include <QRegularExpression>

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

     Q_INVOKABLE void addEvent(QString title, QString desc, QString loc) {
         Event e;
         e.setFounder(my_id);
         e.setTitle(title);
         e.setDesc(desc);
         e.setLocation(loc);
		//   e.setDate(date);
		 //  e.setHow_long(hl);

        _st << MessCodes::create_event;
        _st << e;
        _socket->flush();
        _socket->waitForBytesWritten();
        this->getUser(my_id);
        //qDebug() << user->eventsInvited();
        EventsRefresh();
     }

    void EventsRefresh() {
        availableEvents = user->eventsInvited();

        QList<QObject*> events;

        for (id_type id: availableEvents) {
            events.append(this->getEvent(id));
        }

        engine->rootContext()->setContextProperty("eventsList", QVariant::fromValue(events));
    }

    void FbFriendListRefresh() {
        QList<id_type> fbfriends;

        _st << MessCodes::fb_friends_list;
        _socket->flush();
        _st >> fbfriends;

        QList<QObject*> flist;

        for (id_type id: fbfriends) {
            flist.append(this->getFriend(id));
        }

        engine->rootContext()->setContextProperty("facebookFriendsList", QVariant::fromValue(flist));

    }

    void FriendListRefresh() {
        QList<id_type> friends = user->friends();

        QList<QObject*> flist;

        for (id_type id: friends) {
         flist.append(this->getFriend(id));
        }

        engine->rootContext()->setContextProperty("friendsList", QVariant::fromValue(flist));
    }

    Q_INVOKABLE void delFriend(qint32 id) {
        qDebug() << "usuwam: " << id;
        _st << MessCodes::del_friend;
        _socket->flush();
        _st << id;
        _socket->flush();
        _socket->waitForBytesWritten();
        this->getUser(my_id);
        FriendListRefresh();
     }

    Q_INVOKABLE void addFriend(qint32 id) {
        qDebug() << "dodaje: " << id;
        _st << MessCodes::add_friend;
        _socket->flush();
        _st << id;
        _socket->flush();
        _socket->waitForBytesWritten();
        this->getUser(my_id);
        FriendListRefresh();
    }

     void connect();

     User* getFriend(id_type id)
     {
         _st << MessCodes::user_data;
         _socket->flush();
         _st << id;
         _socket->flush();

         User *u = new User();
         *u = User::readUser(_socket);
         return u;
     }

     Q_INVOKABLE void login() {
         this->connect();
         this->getUser(my_id);
         //EventsRefresh();
         //FriendListRefresh();
         //FbFriendListRefresh();
     }

     Q_INVOKABLE void set_logout_url() {
        QString logoutUrl = QStringLiteral("https://www.facebook.com/logout.php?next=http://localhost/&access_token=");
        logoutUrl.append(token);
        qDebug() << logoutUrl;
        engine->rootContext()->setContextProperty(QStringLiteral("logoutUrl"), logoutUrl);
     }

     Q_INVOKABLE bool access_url(QString url) {
       QRegularExpression re(".+login_success.html#access_token=(.+)&");
       QRegularExpressionMatch match = re.match(url);
       if (match.hasMatch()) {
           QString a = match.captured(1);
           token = a;

           //qDebug() << token << sizeof(token);
           _st << MessCodes::signup;
           _socket->flush();
           _st << (qint32) token.size();
           _st << token;
           _socket->flush();
           _socket->waitForBytesWritten();

           while (_socket->bytesAvailable() < sizeof(id_type)) {
               _socket->waitForReadyRead(1);
           }

           id_type id;
           _st >> id;
           my_id = id;

           qDebug() << "MOJE ID: " << my_id;

           login();
           return true;
       }
       return false;
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
    QString token;
};

#endif // CPPCLASS_H
