#include "commenthandler.h"

commenthandler::commenthandler(QObject *parent) : QObject(parent)
{

}

commenthandler::commenthandler(QString cnt, QString auth, QString dt)
{
    _content = cnt;
    _author = auth;
    _date = dt;
}

commenthandler::~commenthandler()
{

}

QString commenthandler::content() const
{
    return _content;
}

QString commenthandler::author() const
{
    return _author;
}

QString commenthandler::date() const
{
    return _date;
}
