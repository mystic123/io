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
#include "comment.h"
#include "commenthandler.h"
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

     Q_INVOKABLE bool isItMyEvent() {
         return chosenEvent.founder() == my_id;
     }

     Q_INVOKABLE bool amIAttending() {
         return chosenEvent.attending().contains(my_id);
     }

     Q_INVOKABLE void chosenEventModel(qint32 id) {
         id_type id_tmp = id;
         chosenEventId = id_tmp;
         get_event_comments();
     }

     Q_INVOKABLE QString eventDesc() {
         return chosenEvent.desc();
     }

     Q_INVOKABLE QString eventTitle() {
         return chosenEvent.title();
     }

     Q_INVOKABLE QString eventLoc() {
         return chosenEvent.location();
     }

     Q_INVOKABLE void addEvent(QString title, QString desc, QString loc) {
         qDebug() << "dodaje Event:";
         Event e;
         e.setFounder(my_id);
         e.setTitle(title);
         e.setDesc(desc);
         e.setLocation(loc);
         e.setDate(QDateTime::currentDateTime());
         e.setHow_long(1);

        _st << MessCodes::create_event;
        _st << e;
        _socket->flush();
        _socket->waitForBytesWritten();

        while (_socket->bytesAvailable() < sizeof(qint32)) {
            _socket->waitForReadyRead(1);
        }

        qint32 ok;
        _st >> ok;

        this->getUser(my_id);
        EventsRefresh();
    }

    void EventsRefresh() {
        availableEvents = user->eventsInvited();

        QList<QObject*> events;
        qDebug() << "EVENTS INVITED" << user->eventsInvited();
        for (id_type id: availableEvents) {
            events.append(this->getEvent(id));
        }

        engine->rootContext()->setContextProperty("eventsList", QVariant::fromValue(events));
    }

    void FbFriendListRefresh() {
        QList<id_type> fbfriends;

        _st << MessCodes::fb_friends_list;
        _socket->flush();
        _st << (qint32) token.size();
        _st << token;
        _socket->flush();
        _socket->waitForBytesWritten();

        while (_socket->bytesAvailable() < sizeof(qint32)) {
            _socket->waitForReadyRead(REFRESH_TIME);
        }

        qint32 size;
        _st >> size;

        while (_socket->bytesAvailable() < size * sizeof(id_type)) {
            _socket->waitForReadyRead(REFRESH_TIME);
        }
        _st >> fbfriends;
        qDebug()<<fbfriends;

        QList<QObject*> flist;

        for (id_type id: fbfriends) {
            User *tmp = this->getFriend(id);
            if (tmp != nullptr)
                flist.append(tmp);
        }

        engine->rootContext()->setContextProperty("facebookFriendsList", QVariant::fromValue(flist));

    }

    void FriendListRefresh() {
        QList<id_type> friends = user->friends();

        QList<QObject*> flist;

        for (id_type id: friends) {
         flist.append(this->getFriend(id));
         qDebug() << "w refresh" << this->getFriend(id)->id();
        }

        engine->rootContext()->setContextProperty("friendsList", QVariant::fromValue(flist));
    }

    Q_INVOKABLE void eventAttendingRefresh() {
        chosenEvent = *this->getEvent(chosenEventId);
        QList<QObject*> names;
        for(id_type id: chosenEvent.attending()) {
            names.append(this->getFriend(id));
        }

        engine->rootContext()->setContextProperty("attendingList", QVariant::fromValue(names));
    }

    Q_INVOKABLE void joinEvent() {
        _st << MessCodes::join_event;
        _socket->flush();
        qDebug() << "dodaje sie do eventu" << chosenEvent.id();
        _st << chosenEvent.id();
        _socket->flush();
        _socket->waitForBytesWritten();

        while (_socket->bytesAvailable() < sizeof(qint32)) {
            _socket->waitForReadyRead(1);
        }

        qint32 ok;
        _st >> ok;

        eventAttendingRefresh();
     }

    Q_INVOKABLE void delFriend(QString id) {
        id_type id_tmp = id.toLongLong();
        qDebug() << "usuwam: " << id_tmp;
        _st << MessCodes::del_friend;
        _socket->flush();
        _st << id_tmp;
        _socket->flush();
        _socket->waitForBytesWritten();

        while (_socket->bytesAvailable() < sizeof(qint32)) {
            _socket->waitForReadyRead(1);
        }

        qint32 ok;
        _st >> ok;

        this->getUser(my_id);
        FriendListRefresh();
        FbFriendListRefresh();
     }

    Q_INVOKABLE void addFriend(QString id) {
        id_type id_tmp = id.toLongLong();
        qDebug() << "dodaje: " << id_tmp;
        _st << MessCodes::add_friend;
        _socket->flush();
        _st << id_tmp;
        _socket->flush();
        _socket->waitForBytesWritten();

        while (_socket->bytesAvailable() < sizeof(qint32)) {
            _socket->waitForReadyRead(1);
        }

        qint32 ok;
        _st >> ok;

        this->getUser(my_id);
        FriendListRefresh();
        FbFriendListRefresh();
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
         qDebug() << "GET FRIEND ID" << u->id();
         if (u->id() == 0)
             return nullptr;
         else
            return u;
     }

     Q_INVOKABLE void login() {
         this->connect();
         this->getUser(my_id);
         EventsRefresh();
         FriendListRefresh();
         FbFriendListRefresh();
     }

    Q_INVOKABLE void add_comment(QString cnt) {
         qDebug() << "dodaje comment";
         Comment c;
         c.setEvent(chosenEventId);
         c.setAuthorId(my_id);
         c.setContent(cnt);
         c.setDate(QDateTime::currentDateTime());

        _st << MessCodes::add_comment;
        _st << c;
        _socket->flush();
        _socket->waitForBytesWritten();

        while (_socket->bytesAvailable() < sizeof(qint32)) {
            _socket->waitForReadyRead(1);
        }

        qint32 ok;
        _st >> ok;
        qDebug() << "dodaje comment na koncu";
    }


     Q_INVOKABLE void get_event_comments() {
         chosenEvent = *this->getEvent(chosenEventId);
         QList<QObject*> clist;
         for (id_type cid: chosenEvent.comments()) {
              qDebug() << "Pobieram komentarz o id:" << cid;
             _st << MessCodes::comment_data;
             _socket->flush();
             _st << cid;
             _socket->flush();

             Comment *c = new Comment();
             *c = Comment::readComment(_socket);

             qDebug() << c->authorId();

             User *u = this->getFriend(c->authorId());

             QString cnt = c->content();
             QString auth = u->firstName() + " " + u->lastName();
             QString date = c->date().toString();

             qDebug() << "TRESC" << cnt << auth << date;

             clist.append(new commenthandler(cnt, auth, date));
         }

         engine->rootContext()->setContextProperty("commentList", QVariant::fromValue(clist));

       // add_comment(chosenEventId, "LETS TRY THIS OUT");

     }

     Q_INVOKABLE void set_logout_url() {
        QString logoutUrl = QStringLiteral("https://www.facebook.com/logout.php?next=http://localhost/&access_token=");
        logoutUrl.append(token);
        qDebug() << logoutUrl;
        engine->rootContext()->setContextProperty(QStringLiteral("logoutUrl"), logoutUrl);
     }

     Q_INVOKABLE bool fine_url(QString url) {
         QRegularExpression re(".+facebook.com/login.php?.+");
         QRegularExpressionMatch match = re.match(url);
         if (match.hasMatch())
            return true;
         else
            return false;
     }

     Q_INVOKABLE bool access_url(QString url) {
       QRegularExpression re(".+login_success.html#access_token=(.+)&");
       QRegularExpressionMatch match = re.match(url);
       if (match.hasMatch()) {
           QString a = match.captured(1);
           token = a;

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
    id_type chosenEventId;
    Event chosenEvent;
    QString token;
};

#endif // CPPCLASS_H
