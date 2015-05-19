#ifndef COMMENT_H
#define COMMENT_H

#include <QObject>
#include "global.h"

class Comment : public QObject
{
	Q_OBJECT
public:
	explicit Comment(QObject *parent = 0);
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

signals:

public slots:

private:
	id_type _id;
	id_type _eventId;
	id_type _authorId;
	QString _content;
	QDateTime _date;
};

#endif // COMMENT_H
