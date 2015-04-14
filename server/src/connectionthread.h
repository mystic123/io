#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "global.h"
#include "user.h"
#include "dbcontroller.h"

class ConnectionThread : public QThread
{
	Q_OBJECT

public:
	explicit ConnectionThread(qintptr ID, QObject *parent = 0);
	virtual ~ConnectionThread();
	void run();

	static const int max_retries = 5;

signals:
	void error(QTcpSocket::SocketError socketerror);

public slots:
	void readyRead();
	void disconnected();

private:
	typedef void (ConnectionThread::*mem_func)();
	static const QMap<MessCodes, mem_func> _actions;
	void userData();
	void friendsList();
	void eventsList();
	void eventData();
	void createEvent();

	QTcpSocket *_socket;
	qintptr _socket_desc;
	User* _user;
	DBController *_db;


};

#endif // CONNECTIONTHREAD_H
