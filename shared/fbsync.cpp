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
}

void FBsync::setToken(const QString &token)
{
	_token = token;
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
	User u;
	u.setFbId(obj.find("id").value().toString().toLongLong());
	qDebug() << "fbid:" << u.fbId();
	u.setEmail(obj.find("email").value().toString());
	qDebug() << "email:" << u.email();
	u.setFirstName(obj.find("first_name").value().toString());
	qDebug() << "first name:" << u.firstName();
	u.setLastName(obj.find("last_name").value().toString());
	qDebug() << "last name:" << u.lastName();
	u.setGender(obj.find("gender").value().toString().at(0));
	qDebug() << "gender:" << u.gender();
}

void FBsync::fetchFriendsS(QNetworkReply *reply)
{
	QString str = reply->readAll();
	QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
	QJsonArray arr = jsonResponse.object().find("data").value().toArray();
	qDebug() << arr;
	for (QJsonValue x : arr) {
		qDebug() << x.toObject().value("id");
	}
}

