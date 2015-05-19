#include "comment.h"

Comment::Comment(QObject *parent) : QObject(parent)
{

}

Comment::~Comment()
{

}
id_type Comment::id() const
{
	return _id;
}

void Comment::setId(const id_type &id)
{
	_id = id;
}
id_type Comment::eventId() const
{
	return _eventId;
}

void Comment::setEvent(const id_type &eventId)
{
	_eventId = eventId;
}
id_type Comment::authorId() const
{
	return _authorId;
}

void Comment::setAuthorId(const id_type &authorId)
{
	_authorId = authorId;
}
QString Comment::content() const
{
	return _content;
}

void Comment::setContent(const QString &content)
{
	_content = content;
}
QDateTime Comment::date() const
{
	return _date;
}

void Comment::setDate(const QDateTime &date)
{
	_date = date;
}






