#include "client.h"
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include "global.h"

Client::Client(QObject *parent) : QObject(parent)
{

}

Client::~Client()
{

}

Event Client::sendMessage()
{
    QTcpSocket *_socket = new QTcpSocket();
    //_socket->connectToHost("89.72.66.74", 10666);
    _socket->connectToHost("127.0.0.1", 12000);
    _socket->waitForConnected();

    connect(_socket, SIGNAL(readyRead()), this, SLOT(test()));

    qDebug() << _socket->state();
    QDataStream st(_socket);
    id_type id = 12;
    st << id;


    st << MessCodes::event_data;
    id_type id2 = 14;
    st << id2;
    Event e;
    _socket->waitForReadyRead();
    st >> e;

    qDebug() << "w f:" + e.desc() + " id: " + QString::number(e.id());
    return e;

//    QStringList dataList;
//    dataList.append("Item 1");
//    dataList.append("Item 2");
//    dataList.append("Item 3");
//    dataList.append("Item 4");
//    dataList.append("Item 5");
//    return dataList;
}
