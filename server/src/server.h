#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server : public QTcpServer
{
	Q_OBJECT

public:
	explicit Server(QObject *parent = 0);
	~Server();
	void startServer();
	void foo();

protected:
	void incomingConnection(qintptr socket_desc);
};

#endif // SERVER_H
