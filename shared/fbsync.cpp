#include "fbsync.h"

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

const QString FBsync::APP_ID = "1615817788631871";
const QString FBsync::APP_SECRET = "83ce02d3d91543dc4671f47de0e71a20";

FBsync::FBsync(QObject *parent) : QObject(parent), _token("")
{
}

FBsync::~FBsync()
{
}

void FBsync::fetchData()
{
	fetchUserData();
	fetchFriends();
	emit userDataReady();
}

void FBsync::setToken(const QString &token)
{
	_token = token;
}

User *FBsync::getUser() const
{
	return _user;
}

void FBsync::fetchUserData()
{
	QUrlQuery urlQuery;
	urlQuery.setQuery("https://graph.facebook.com/me?");
	urlQuery.addQueryItem("access_token", _token);
	QNetworkRequest request;
	request.setUrl(QUrl(urlQuery.query()));
	QNetworkAccessManager *mgr = new QNetworkAccessManager(this);
	connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(fetchUserDataS(QNetworkReply*)));
	mgr->get(request);
}

void FBsync::fetchFriends()
{
	QUrlQuery urlQuery;
	urlQuery.setQuery("https://graph.facebook.com/me/friends?");
	urlQuery.addQueryItem("access_token", _token);
	QNetworkRequest request;
	request.setUrl(QUrl(urlQuery.query()));
	QNetworkAccessManager *mgr = new QNetworkAccessManager(this);
	connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(fetchFriendsS(QNetworkReply*)));
	mgr->get(request);
}

void FBsync::fetchUserDataS(QNetworkReply *reply)
{
	QString str = reply->readAll();
	QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
	QJsonObject obj = jsonResponse.object();
	_user = new User();
    //_user->setFbId(obj.find("id").value().toString().toLongLong());
    //qDebug() << "fbid:" << _user->fbId();
	_user->setEmail(obj.find("email").value().toString());
	qDebug() << "email:" << _user->email();
	_user->setFirstName(obj.find("first_name").value().toString());
	qDebug() << "first name:" << _user->firstName();
	_user->setLastName(obj.find("last_name").value().toString());
	qDebug() << "last name:" << _user->lastName();
	_user->setGender(obj.find("gender").value().toString().at(0));
	qDebug() << "gender:" << _user->gender();
}

void FBsync::fetchFriendsS(QNetworkReply *reply)
{
	QString str = reply->readAll();
	QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
	QJsonArray arr = jsonResponse.object().find("data").value().toArray();
	qDebug() << arr;
	for (QJsonValue x : arr) {
		qDebug() << x.toObject().value("id");
		_user->addFriend(x.toObject().value("id").toString().toULongLong());
		qDebug() << "added:" << x.toObject().value("id").toString().toULongLong();
	}
}

