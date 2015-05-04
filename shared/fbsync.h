#ifndef FBSYNC_H
#define FBSYNC_H

#include <QObject>
#include <QNetworkReply>

#include "global.h"
#include "user.h"

class FBsync : public QObject
{
	Q_OBJECT

public:
	explicit FBsync(QObject *parent = 0);
	~FBsync();

	void fetchData();
	void setToken(const QString& token);

signals:

private slots:
	void fetchUserDataS(QNetworkReply*);
	void fetchFriendsS(QNetworkReply*);

private:
	void fetchUserData();
	void fetchFriends();

	static const QString APP_ID;
	static const QString APP_SECRET;
	QString _token;

};

#endif // FBSYNC_H