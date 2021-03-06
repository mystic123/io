#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QRunnable>

#include "global.h"
#include "user.h"
#include "dbcontroller.h"

class Server;

class ConnectionThread : public QThread, public QRunnable
{
	Q_OBJECT

public:
	explicit ConnectionThread(Server *parent, int id, QWaitCondition& wait);
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

	void handleConnection();

	void login();
	void userData();
	void delUser();
	void friendsList();
	void eventData();
	void createEvent();
	void updateEvent();
	void joinEvent();
	void addFriend();
	void delFriend();
	void signup();
	void fbFriendsList();
	void commentData();
	void addComment();
	void updateComment();
	void delComment();

	/* testing functions */
	void createUserDbg();

	void sendOK();
	void sendError();

	Server* _parent;
	const int _id;
	QTcpSocket *_socket;
	qintptr _socket_desc;
	QDataStream _stream;
	User* _user;
	DBController *_db;

	QMutex _mtx;
	QWaitCondition& _wait;

};

#endif // CONNECTIONTHREAD_H
