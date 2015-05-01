#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QRunnable>

#include "global.h"
#include "user.h"
#include "dbcontroller.h"

class Server;

class ConnectionThread : public QThread, QRunnable
{
	Q_OBJECT

public:
	explicit ConnectionThread(qintptr ID, Server *parent = 0);
	virtual ~ConnectionThread();
	void run();

	static const int MAX_RETRY = 5;

signals:
	void error(QTcpSocket::SocketError socketerror);

public slots:
	void readyRead();
	void disconnected();

private:
	typedef void (ConnectionThread::*mem_func)();
	static const QMap<MessCodes, mem_func> _actions;
	void login();
	void userData();
	void friendsList();
	//void eventsList();
	void eventData();
	void createEvent();
	void updateEvent();
	void inviteEvent();
	void joinEvent();
	void addFriend();
	void delFriend();

	Server *_parent;
	QTcpSocket *_socket;
	qintptr _socket_desc;
	QDataStream _stream;
	User* _user;
	DBController *_db;

};

#endif // CONNECTIONTHREAD_H
