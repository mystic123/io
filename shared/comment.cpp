#include "comment.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QDateTime>

Comment::Comment(QObject *parent) : QObject(parent)
{
	_id = 0;
	_eventId = 0;
	_authorId = 0;
	_content = "";
	_date = QDateTime();
}

Comment::Comment(const Comment &c)
{
	_id = c.id();
	_eventId = c.eventId();
	_authorId = c.authorId();
	_content = c.content();
	_date = c.date();
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

void Comment::operator=(const Comment &c)
{
	_id = c.id();
	_eventId = c.eventId();
	_authorId = c.authorId();
	_content = c.content();
	_date = c.date();
}

bool Comment::operator==(const Comment &c)
{
	if (_id != c.id()) {
		return false;
	}
	if (_eventId != c.eventId()) {
		return false;
	}
	if (_authorId != c.authorId()) {
		return false;
	}
	if (_content != c.content()) {
		return false;
	}
	if (_date != c.date()) {
		return false;
	}
	return true;
}

QDataStream& operator<<(QDataStream &out, const Comment &c)
{
	QByteArray array;
	QDataStream stream(&array, QIODevice::WriteOnly);
	stream << c._id << c._authorId << c._eventId << c._content << c._date;
	out << array;
	return out;
}

QDataStream& operator>>(QDataStream &in, Comment &c)
{
	in >> c._id >> c._authorId >> c._eventId >> c._content >> c._date;
	return in;
}

Comment Comment::readComment(QTcpSocket *s)
{
	QDataStream d(s);
	while (s->bytesAvailable() < sizeof(qint32)) {
		s->waitForReadyRead(REFRESH_TIME);
	}

	qint32 size;
	d >> size;

	while (s->bytesAvailable() < size) {
		s->waitForReadyRead(REFRESH_TIME);
	}

	Comment c;
	d >> c;
	return c;
}






