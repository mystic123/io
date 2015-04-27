#include "cppclass.h"
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>

CppClass::CppClass(QObject *parent) : QObject(parent)
{

}

CppClass::~CppClass()
{

}

QStringList CppClass::sendMessage()
{

    QTcpSocket *_socket = new QTcpSocket();
    _socket->connectToHost("172.20.10.2", 10666);
    _socket->waitForConnected();

    qDebug() << _socket->state();
    QDataStream st(_socket);
    qint32 id = 12;
    st << id;
    _socket->flush();
    _socket->waitForBytesWritten();

    QStringList dataList;
    dataList.append("Item 1");
    dataList.append("Item 2");
    dataList.append("Item 3");
    dataList.append("Item 4");
    dataList.append("Item 5");
    return dataList;
}
