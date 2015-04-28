#ifndef CPPCLASS_H
#define CPPCLASS_H

#include <QObject>
#include <QQuickItem>
#include <QQuickTextDocument>
#include <QTextDocument>
#include "event.h"
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include "global.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();

    Q_INVOKABLE Event sendMessage();

signals:

public slots:
	 void test();

private:
    //QStringList<event>
    Event e;
	 QTcpSocket *_socket;
	 QDataStream _st;
};

#endif // CPPCLASS_H
