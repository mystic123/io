#include "server.h"
#include "connectionthread.h"
#include <QHostAddress>

Server::Server(QObject *parent): QTcpServer(parent)
{
}

Server::~Server()
{
}

void Server::startServer()
{

	if(!this->listen(QHostAddress::Any, Server::port)) {
		qDebug()<<"Could not start server\n";
	}
	else {
		qDebug()<<"Listening to port: "<<port<<endl;
	}

}

void Server::incomingConnection(qintptr socket_desc)
{
	qDebug()<<socket_desc<<"Connecting...\n";

	ConnectionThread *thread = new ConnectionThread(socket_desc, this);

	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

	QThreadPool::globalInstance()->start(thread);
//	thread->start();
}