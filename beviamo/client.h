#ifndef CPPCLASS_H
#define CPPCLASS_H

#include <QObject>
#include <QQuickItem>
#include <QQuickTextDocument>
#include <QTextDocument>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>

#include "event.h"
#include "global.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();

	 Q_INVOKABLE Event getEventData(id_type);

signals:

public slots:

private:
    //QStringList<event>
	 QTcpSocket *_socket;
	 QDataStream _st;
};

#endif // CPPCLASS_H
