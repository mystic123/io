#include <iostream>
#include "fbsync.h"
#include <QSqlQuery>
#include "user.h"
#include "event.h"
#include "comment.h"
#include "dbcontroller.h"
#include "global.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QDateTime>

using namespace std;

QTcpSocket *socket;
QDataStream st;

void testCreateUser(){
	qDebug() << QString("createUser");
	DBController d(1415);
	for (qint16 i = 1; i<= 20; i++){
		  User u;
		  u.setId(i);
		  u.setEmail("user" + QVariant(i).toString() + "@mail.pl");
		  u.setFirstName("przed update "+ QVariant(i).toString());
		  u.setLastName("drugie imie  " + QVariant(i).toString());
		  u.setGender('m');
		  u.setFriends({});
		  u.setEventsAttending({});
		  u.setEventsInvited({});
		  d.createUser(u);
	}
}

void testCreateEvent(){
	qDebug() << QString("createEvent");
	DBController d(1414);
	for (qint16 i = 1; i<= 20; i++){
		  Event e;
		  e.setFounder(i);
		  e.setTitle("Wydarzenie numer " + QVariant(i).toString());
		  e.setDesc("Opis "+ QVariant(i).toString());
		  e.setDate(QDateTime(QDate(2015+i,7,i+1), QTime(i,0,i)));
		  e.setInvited({2});
		  e.setAttending({2});
		  e.setHow_long(2);
		  e.setLocation("warszawa");
		  d.createEvent(e);
	}
}

void testUpdateEvent(){
	 qDebug() << QString("updateEvent");
	 DBController d(1212);
	 for(qint16 i = 1; i<= 10; i++){
		  Event e;
		  e.setId(i);
		  e.setFounder(i);
		  e.setTitle("Wydarzenie numer " + QVariant(i).toString());
		  e.setDesc("Opis updated "+ QVariant(i).toString());
		  e.setDate(QDateTime(QDate(2015+i,7,i+1), QTime(i,0,i)));
		  e.setInvited({});
		  e.setAttending({});
		  e.setHow_long(3);
		  e.setLocation("warszawa");
		  d.updateEvent(e);
	 }
	 for(qint16 i = 11; i<= 20; i++){
		  Event e;
		  e.setId(i);
		  e.setFounder(i);
		  e.setTitle("Wydarzenie numer " + QVariant(i).toString());
		  e.setDesc("Opis updated "+ QVariant(i).toString());
		  e.setDate(QDateTime(QDate(2015+i,7,i+1), QTime(i,0,i)));
		  e.setInvited({1,3});
		  e.setAttending({1});
		  e.setHow_long(3);
		  e.setLocation("warszawa");
		  d.updateEvent(e);
	 }
}

void testUpdateUser(){
	 qDebug() << QString("updateUser");
	 DBController d(14222);
	 for(qint16 i = 1; i<= 10; i++){
		  User u;
		  u.setId(i);
		  u.setEmail("user " + QVariant(i).toString() + "@bla.pl");
		  u.setFirstName("po update "+ QVariant(i).toString());
		  u.setLastName("po update " + QVariant(i).toString());
		  u.setGender('f');
		  u.setFriends({1,2,3,4,5});
		  u.setEventsAttending({1,2,3});
		  u.setEventsInvited({1,2});
		  d.updateUser(u);
	 }
	 for(qint16 i = 11; i<= 20; i++){
		  User u;
		  u.setId(i);
		  u.setEmail("user " + QVariant(i).toString() + "@bla.pl");
		  u.setFirstName("po update "+ QVariant(i).toString());
		  u.setLastName("drugie imie " + QVariant(i).toString());
		  u.setGender('f');
		  u.setFriends({});
		  u.setEventsAttending({});
		  u.setEventsInvited({});
		  d.updateUser(u);
	  }
}

void testRemoveUser(){
	  qDebug() << QString("removeUser");
	 DBController d(122);
	 for(qint16 i = 1; i<= 20; i++){
		  User u;
		  u.setId(i);
		  d.removeUser(u);
	 }
}

void testRemoveEvent(){
	 qDebug() << QString("removeEvent");
	 DBController d(142);
	 for(qint16 i = 1; i<= 20; i++){
		  Event e;
		  e.setId(i);
		  d.removeEvent(e);
	 }
}

void testCreateComment(){
	 qDebug() << QString("createComment");
	DBController d(1312);
	for (qint16 i = 1; i<= 20; i++){
		  Comment c;
		  c.setEvent(i);
		  c.setAuthorId(i);
		  c.setContent("tutaj komentuje");
		  c.setDate(QDateTime(QDate(2015+i,7,i+1), QTime(i,0,i)));
		  d.createComment(c);
	}
}

void testUpdateComment(){
	 qDebug() << QString("updateComment");
	 DBController d(7434);
	 for(qint16 i = 1; i<= 20; i++){
		  Comment c;
		  c.setId(i);
		  c.setEvent(i);
		  c.setAuthorId(i);
		  c.setContent("tutaj komentuje po update");
		  c.setDate(QDateTime(QDate(2015+i,7,i+1), QTime(i,0,i)));
		  d.updateComment(c);
	}
}

void testRemoveComment(){
	 qDebug() << QString("removeComment");
	 DBController d(1712);
	 for(qint16 i = 1; i<= 5; i++){
		  Comment c;
		  c.setId(i);
		  d.removeComment(c);
	 }
}

void testGetEvent(){
	qDebug() << QString("getEvent");
	DBController d(1792);
	for(qint16 i = 1; i<= 20; i++){
		 Event *e;
		 e = d.getEvent(i);
		 if (e->desc() != ("Opis updated " + QVariant(i).toString())){
			  qDebug() << "getEvent desc error";
			  exit(0);
		 }
	}
}

void testGetUser(){
	qDebug() << QString("getUser");
	DBController d(1392);
	for(qint16 i = 6; i<= 20; i++){
		 User *u;
		 u = d.getUserById(i);
		 if (u->firstName() != ("po update " + QVariant(i).toString())){
			  qDebug() << u->firstName();
			  qDebug() << "po update " + QVariant(i).toString();
			  qDebug() << "getUser firstName error";
			  exit(0);
		 }
	}
}

bool testLogin(const User &u)
{
	st << MessCodes::login;

	st << u.id();

	while (socket->bytesAvailable() < sizeof(MessCodes)) {
		socket->waitForReadyRead(REFRESH_TIME);
	}

	MessCodes c;
	st >> c;
	if (c != MessCodes::ok) {
		return false;
	}

	return true;
}

User testSignup(QString token)
{
	//st << MessCodes::signup;
	st << (qint32) token.size();
	st << token;
	socket->waitForBytesWritten();

	while (socket->bytesAvailable() < sizeof(MessCodes)) {
		socket->waitForReadyRead(REFRESH_TIME);
	}

	MessCodes c;
	st >> c;

	if (c != MessCodes::ok) {
		qDebug() << "Error. Wrong token?";
		User u;
		return u;
	}

	while (socket->bytesAvailable() < sizeof(id_type)) {
		socket->waitForReadyRead(REFRESH_TIME);
	}
	id_type id;
	st >> id;

	st << MessCodes::user_data;

	st << id;
	socket->flush();
	User u1 = User::readUser(socket);

	qDebug() << "Successfully signed as" << u1.firstName() << u1.lastName();
	return u1;
}

bool testCreateUserS(const User &u)
{
	st << MessCodes::create_userDEBUG;
	st << u;

	while (socket->bytesAvailable() < sizeof(MessCodes)) {
		socket->waitForReadyRead(REFRESH_TIME);
	}

	MessCodes c;
	st >> c;
	if (c != MessCodes::ok) {
		return false;
	}
	return true;
}

bool testUserData(const User &u)
{
	st << MessCodes::user_data;

	st << u.id();

	User u1 = User::readUser(socket);

	return (u1 == u);
}

bool testCreateEvent(Event &e)
{
	st << MessCodes::create_event;

	st << e;

	while (socket->bytesAvailable() < sizeof(MessCodes)) {
		socket->waitForReadyRead(REFRESH_TIME);
	}
	MessCodes c;
	st >> c;
	if (c != MessCodes::ok) {
		return false;
	}

	st << MessCodes::user_data;

	st << e.founder();

	User u = User::readUser(socket);

	e.setId(u.eventsAttending().first());

	st << MessCodes::event_data;

	st << e.id();
	Event e1 = Event::readEvent(socket);

	return (e == e1);
}

bool testCreateMEvent(Event &e)
{
	st << MessCodes::create_event;

	/* setting malformed founder */
	e.setFounder(1231232413421);
	st << e;

	while (socket->bytesAvailable() < sizeof(MessCodes)) {
		socket->waitForReadyRead(REFRESH_TIME);
	}
	MessCodes c;
	st >> c;
	if (c != MessCodes::error) {
		return false;
	}
	return true;
}

bool testEventData(const Event &e)
{
	st << MessCodes::event_data;

	st << e.id();
	Event e1 = Event::readEvent(socket);

	return (e == e1);
}

bool testUpdateEvent(Event& e)
{
	e.setDesc("new desc");

	st << MessCodes::update_event;

	st << e;

	while (socket->bytesAvailable() < sizeof(MessCodes)) {
		socket->waitForReadyRead(REFRESH_TIME);
	}

	MessCodes code;
	st >> code;

	if (code != MessCodes::ok)
		return false;

	st << MessCodes::event_data;

	st << e.id();

	Event ne = Event::readEvent(socket);

	return (ne == e);
}

bool testMEventData()
{
	st << MessCodes::event_data;

	id_type id = 123124;
	st << id;
	Event e1 = Event::readEvent(socket);

	return (e1.id() == 0);
}

bool testUpdateMEvent(Event& e)
{
	e.setDesc("new desc");
	e.setFounder(132432412);

	st << MessCodes::update_event;

	st << e;

	while (socket->bytesAvailable() < sizeof(MessCodes)) {
		socket->waitForReadyRead(REFRESH_TIME);
	}

	MessCodes code;
	st >> code;

	return (code == MessCodes::error);
}

bool testJoinEvent(Event& e, const User& u)
{
	st << MessCodes::join_event;

	st << e.id();

	while (socket->bytesAvailable() < sizeof(MessCodes)) {
		socket->waitForReadyRead(REFRESH_TIME);
	}

	MessCodes code;
	st >> code;

	if (code != MessCodes::ok)
		return false;

	st << MessCodes::event_data;

	st << e.id();
	e = Event::readEvent(socket);

	return e.attending().contains(u.id());
}

bool testAddFriend(User &u1, const User &u2)
{
	st << MessCodes::add_friend;

	st << u2.id();

	while (socket->bytesAvailable() < sizeof(MessCodes)) {
		socket->waitForReadyRead(REFRESH_TIME);
	}

	MessCodes code;
	st >> code;

	if (code != MessCodes::ok)
		return false;

	st << MessCodes::user_data;

	st << u1.id();

	u1 = User::readUser(socket);

	return (u1.friends().contains(u2.id()));
}

bool testDelFriend(User &u1, const User &u2)
{
	st << MessCodes::del_friend;

	st << u2.id();

	while (socket->bytesAvailable() < sizeof(MessCodes)) {
		socket->waitForReadyRead(REFRESH_TIME);
	}

	MessCodes code;
	st >> code;

	if (code != MessCodes::ok)
		return false;

	st << MessCodes::user_data;

	st << u1.id();

	u1 = User::readUser(socket);

	return !(u1.friends().contains(u2.id()));
}

bool testCommentData(const Comment &c)
{
	st << MessCodes::comment_data;

	st << c.id();

	Comment c1 = Comment::readComment(socket);

	return (c1 == c);
}

bool testAddComment(const Comment &c)
{
	st << MessCodes::add_comment;

	st << c;

	while (socket->bytesAvailable() < sizeof(MessCodes)) {
		socket->waitForReadyRead(REFRESH_TIME);
	}

	MessCodes code;
	st >> code;

	if (code != MessCodes::ok)
		return false;

	st << MessCodes::comment_data;

	st << c.id();

	Comment c1 = Comment::readComment(socket);

	return (c1 == c);
}

bool testRemoveUserS()
{
	st << MessCodes::del_user;

	while (socket->bytesAvailable() < sizeof(MessCodes)) {
		socket->waitForReadyRead(REFRESH_TIME);
	}

	MessCodes code;
	st >> code;

	return (code == MessCodes::ok);
}

int main(int argc, char *argv[])
{
	 /*   przed uzyciem wyczyscic baze danych
		*  /io/db/removeDB.sql
		*  /io/db/createDB.sql
	 */

	/* db tests */
	/*
	qDebug() << "Database tests...\n";
	 testCreateUser();
	 testUpdateUser();
	 testCreateEvent();
	 testCreateComment();
	 testUpdateComment();
	 testUpdateEvent();
	 testGetEvent();
	 testGetUser();
	 testRemoveEvent();
	 testRemoveUser();

	 qDebug() << "---------------------------------------------------------------";
	 */
	 qDebug() << "Server tests...\n";
		/* prepare data */
	 socket = new QTcpSocket();
	 QString ip = "localhost";
	 qint16 port = 10777;
	 socket->connectToHost(ip, port);
	 socket->waitForConnected();
	 if (socket->state() != QTcpSocket::ConnectedState) {
		 qDebug() << "Cant connect to server on:" << ip << ":" << port;
		 return 0;
	 }

	 //id_type uid = testSignup();

	 User u2;
	 u2.setId(123321);
	 u2.setEmail("mail@mail.com");
	 u2.setFirstName("first name");
	 u2.setLastName("last name");
	 u2.setGender('m');

	 Event e;
	 e.setTitle("event title");
	 e.setDesc("event desc");
	 e.setLocation("event location");
	 e.setDate(QDateTime(QDateTime::currentDateTime()));
	 e.setHow_long(1);
	 e.setInvited({});
	 e.setAttending({});

	 st.setDevice(socket);

	qDebug() << "Signing in:";
	qDebug() << "Enter token:";
	string token;
	cin >> token;
	User u1 = testSignup(QString::fromStdString(token));
	if (u1.id() != 0) {

		qDebug() << "Fetched data:";
		qDebug() << u1.toString();
		e.setFounder(u1.id());
	 qDebug() << "Testing create event: " << ((testCreateEvent(e)) ? "OK" : "ERROR!");
	 qDebug() << "Testing event data: " << ((testEventData(e)) ? "OK" : "ERROR!");
	 qDebug() << "Testing update event: " << ((testUpdateEvent(e)) ? "OK" : "ERROR!");

	 qDebug() << "Creating other test user...";
	 qDebug() << "User 2: " << ((testCreateUserS(u2)) ? "OK" : "ERROR!");

	 qDebug() << "Testing add friend: " << ((testAddFriend(u1,u2)) ? "OK" : "ERROR!");
	 qDebug() << "Testing del friend: " << ((testDelFriend(u1,u2)) ? "OK" : "ERROR!");
	 testAddFriend(u1,u2);

	 testLogin(u2);
	 qDebug() << "Testing join event: " << ((testJoinEvent(e,u2)) ? "OK" : "ERROR!");

	 qDebug() << "Removing User 2: " << ((testRemoveUserS()) ? "OK" : "ERROR!");

	 socket->disconnectFromHost();
	 socket->readAll();
	 socket->connectToHost(ip, port);
	 socket->waitForConnected();
	 if (socket->state() != QTcpSocket::ConnectedState) {
		 qDebug() << "Cant connect to server on:" << ip << ":" << port;
		 return 0;
	 }

	 u1 = testSignup(QString::fromStdString(token));
	 qDebug() << "Removing User 1: " << ((testRemoveUserS()) ? "OK" : "ERROR!");

	 socket->disconnectFromHost();
	 socket->connectToHost(ip, port);
	 socket->waitForConnected();
	 if (socket->state() != QTcpSocket::ConnectedState) {
		 qDebug() << "Cant connect to server on:" << ip << ":" << port;
		 return 0;
	 }

		u1 = testSignup(QString::fromStdString(token));

	qDebug() << "Testing creating malformed event: " << ((testCreateMEvent(e)) ? "OK" : "ERROR!");
	qDebug() << "Testing malformed event data: " << ((testMEventData()) ? "OK" : "ERROR!");
	qDebug() << "Testing update malformed event: " << ((testUpdateMEvent(e)) ? "OK" : "ERROR!");
	qDebug() << "Removing User 1: " << ((testRemoveUserS()) ? "OK" : "ERROR!");
	}
	socket->disconnectFromHost();
	return 0;
}
