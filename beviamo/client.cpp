#include "client.h"
#include "user.h"


Client::Client(QObject *parent) : QObject(parent)
{

}

Client::~Client()
{

}

void Client::connect()
{
    _socket = new QTcpSocket();
    _socket->connectToHost("192.168.1.111", 10666);
    _socket->waitForConnected();
    qDebug() << _socket->state();
    _st.setDevice(_socket);
    _st << MessCodes::login;
    _st << my_id;
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

void Client::getUser()
{
    _st << MessCodes::user_data;
    _socket->flush();
    _st << my_id;
    _socket->flush();
    User *u = new User();
    *u = User::readUser(_socket);
    this->user = u;
}
