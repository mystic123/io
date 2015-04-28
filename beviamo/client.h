#ifndef CPPCLASS_H
#define CPPCLASS_H

#include <QObject>
#include <QQuickItem>
#include <QQuickTextDocument>
#include <QTextDocument>
#include "event.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();

    Q_INVOKABLE Event sendMessage();

signals:

public slots:
    void test() { qDebug() << "tu" ;}

private:
    //QStringList<event>
    Event e;
};

#endif // CPPCLASS_H
