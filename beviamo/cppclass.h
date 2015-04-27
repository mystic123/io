#ifndef CPPCLASS_H
#define CPPCLASS_H

#include <QObject>
#include <QQuickItem>
#include <QQuickTextDocument>
#include <QTextDocument>

class CppClass : public QObject
{
    Q_OBJECT
public:
    explicit CppClass(QObject *parent = 0);
    ~CppClass();

    Q_INVOKABLE QStringList sendMessage();

signals:

public slots:
};

#endif // CPPCLASS_H
