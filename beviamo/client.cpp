#include "client.h"
#include "user.h"


Client::Client(QObject *parent) : QObject(parent)
{
    _socket = new QTcpSocket();
    _socket->connectToHost("10.20.4.165", 10777);
    _socket->waitForConnected();
    qDebug() << _socket->state();
    _st.setDevice(_socket);
}

Client::~Client()
{

}

void Client::connect()
{
    _st << MessCodes::login;
    _socket->flush();
    _socket->waitForBytesWritten();
    _st << my_id;
    qDebug() << "LOGIN ID " << my_id;
    _socket->flush();
    _socket->waitForBytesWritten();
}

Event* Client::getEvent(id_type id)
{
    _st << MessCodes::event_data;
    _socket->flush();
    _st << id;
    _socket->flush();

    Event *e = new Event();
    *e = Event::readEvent(_socket);
    return e;
}

User* Client::getUser(id_type id)
{
    _st << MessCodes::user_data;
    _socket->flush();
    _st << id;
    _socket->flush();
    User *u = new User();
    *u = User::readUser(_socket);
    //qDebug() << u->eventsInvited();
    this->user = u;
    return u;
}
