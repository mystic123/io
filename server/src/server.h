#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QThreadPool>
#include <QMutex>
#include <QQueue>

class ConnectionThread;

class Server : public QTcpServer
{
	Q_OBJECT

public:
	explicit Server(QObject *parent = 0);
	virtual ~Server();
	void startServer();
protected:
	void incomingConnection(qintptr socket_desc);

private:
	 static const int port = 10666;
	static const int ThreadPoolSize = 100;
};

#endif // SERVER_H
