#ifndef COMMENTHANDLER_H
#define COMMENTHANDLER_H

#include <QObject>

class commenthandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString content READ content CONSTANT)
    Q_PROPERTY(QString author READ author CONSTANT)
    Q_PROPERTY(QString date READ date CONSTANT)

public:
    explicit commenthandler(QObject *parent = 0);
    commenthandler(QString cnt, QString auth, QString dt);
    ~commenthandler();

    QString content() const;
    QString author() const;
    QString date() const;

private:
    QString _content;
    QString _author;
    QString _date;
};

#endif // COMMENTHANDLER_H
