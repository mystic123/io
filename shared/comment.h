#ifndef COMMENT_H
#define COMMENT_H

#include <QObject>
#include "global.h"

class QTcpSocket;
class QDateTime;

class Comment : public QObject
{
	Q_OBJECT
public:
	explicit Comment(QObject *parent = 0);
	Comment(const Comment&);
	~Comment();

	id_type id() const;
	void setId(const id_type &id);

	id_type eventId() const;
	void setEvent(const id_type &eventId);

	id_type authorId() const;
	void setAuthorId(const id_type &authorId);

	QString content() const;
	void setContent(const QString &content);

	QDateTime date() const;
	void setDate(const QDateTime &date);

	/* operators */
	void operator=(const Comment&);
	bool operator==(const Comment&);

	/* serialization */
	friend QDataStream& operator<<(QDataStream&, const Comment&);
	friend QDataStream& operator>>(QDataStream&, Comment&);

	/* static functions */
	static Comment readComment(QTcpSocket*);

private:
	id_type _id;
	id_type _eventId;
	id_type _authorId;
	QString _content;
	QDateTime _date;
};

#endif // COMMENT_H
