#include "server.h"
#include "connectionthread.h"
#include <QHostAddress>

Server::Server(QObject *parent): QTcpServer(parent)//, threads(new QThread*[Server::ThreadPool])
{
}

Server::~Server()
{

}

void Server::startServer()
{
	int port = 2040;

	/*
	for (int i=0; i<Server::ThreadPool; i++) {
		_threads = new ConnectionThread(i, this);
	}
	*/
	if(!this->listen(QHostAddress::Any, port)) {
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

	thread->start();
}
