#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
//#include <QMutex>

//class ConnectionThread;

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
	//static const int ThreadPool = 100;
	//const ConnectionThread** _threads;
};

#endif // SERVER_H
