#ifndef USER_H
#define USER_H

#include <QList>
#include <QChar>

#include "global.h"

class QTcpSocket;

class User : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString fName READ firstName)
	Q_PROPERTY(QString lName READ lastName)
    Q_PROPERTY(QString user_id READ id_string)

public:
	/* constructors */
	explicit User(QObject *parent =0);
	explicit User(const id_type, const QList<id_type>&, const QList<id_type>&, const QList<id_type>&);
	User(const User&);

   virtual ~User();

	/* getters */
	id_type id() const;
    QString id_string() const {
        QString ret = QString::number(id());
        qDebug() << ret;
        return ret;
    }
	QString email() const;
	QString firstName() const;
	QString lastName() const;
	QString name() const;
	QChar gender() const;
	QList<id_type> friends() const;
	QList<id_type> eventsAttending() const;
	QList<id_type> eventsInvited() const;

	/* setters */
	void setId(const id_type &id);
	void setEmail(const QString &email);
	void setFirstName(const QString &firstName);
	void setLastName(const QString &lastName);
	void setGender(const QChar &gender);
	void setFriends(const QList<id_type> &friends);
	void setEventsAttending(const QList<id_type> &eventsAttending);
	void setEventsInvited(const QList<id_type> &eventsInvited);

	void addFriend(id_type);
	void addFriend(const QList<id_type>&);
	void delFriend(id_type);
	void delFriend(const QList<id_type>&);
	void inviteToEvent(id_type);
	void joinEvent(id_type);

	/* opertators */
	void operator=(const User&);
	bool operator==(const User&);

	/* serialization */
	friend QDataStream& operator<<(QDataStream&, const User&);
	friend QDataStream& operator>>(QDataStream&, User&);

	/* static functions */
	static User readUser(QTcpSocket*);

private:
	id_type _id;
	QString _email;
	QString _firstName;
	QString _lastName;
	QChar _gender;
	QList<id_type> _friends;
	QList<id_type> _eventsAttending;
	QList<id_type> _eventsInvited;

};

#endif // USER_H
