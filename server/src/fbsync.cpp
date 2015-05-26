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

FBsync::FBsync(QObject *parent) : QObject(parent), _token(""), _user(nullptr), _dataReady(false), _friendsReady(false), _wasError(false)
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

QList<id_type> FBsync::friendsList()
{
	if (_user.id() != 0) {
		return _user.friends();
		emit userDataReady();
	}
	else {
		fetchData();
		return _user.friends();
	}
}

void FBsync::setToken(const QString &token)
{
	_token = token;
}

User FBsync::getUser() const
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
bool FBsync::wasError() const
{
	return _wasError;
}

void FBsync::fetchUserDataS(QNetworkReply *reply)
{
	QString str = reply->readAll();
	QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
	QJsonObject obj = jsonResponse.object();
	if (obj.find("error") != obj.end()) {
		qDebug() << "error in fetch userdatas";
		_wasError = true;
		emit error();
		return;
	}

	_user.setId(obj.find("id").value().toString().toLongLong());
	_user.setEmail(obj.find("email").value().toString());
	_user.setFirstName(obj.find("first_name").value().toString());
	_user.setLastName(obj.find("last_name").value().toString());
	_user.setGender(obj.find("gender").value().toString().at(0));

	_dataReady = true;
	if (_friendsReady)
		emit userDataReady();
}

void FBsync::fetchFriendsS(QNetworkReply *reply)
{
	QString str = reply->readAll();
	QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
	if (jsonResponse.object().find("error") != jsonResponse.object().end()) {
		qDebug() << "error in fetch friends";
		_wasError = true;
		emit error();
		return;
	}

	QJsonArray arr = jsonResponse.object().find("data").value().toArray();

	for (QJsonValue x : arr) {
		_user.addFriend(x.toObject().value("id").toString().toULongLong());
	}

	_friendsReady = true;
	if (_dataReady)
		emit userDataReady();
}

