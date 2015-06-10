#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QThreadPool>
#include <QMutex>
#include <QQueue>
#include <QtCore>

class ConnectionThread;

class Server : public QTcpServer
{
	Q_OBJECT

public:
	explicit Server(QObject *parent = 0);
	virtual ~Server();
	void startServer();

	qintptr nextClient();
	bool clientWaiting();

protected:
	void incomingConnection(qintptr socket_desc);

private:
	static const int port = 10777;
	static const int threadCount;

	QVector<ConnectionThread*> threads;
	QMutex queue_mutex;
	QWaitCondition connection_waiting;
	QQueue<qintptr> waiting_connections;
};

#endif // SERVER_H
