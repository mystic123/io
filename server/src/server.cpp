#include "server.h"
#include "connectionthread.h"
#include <QHostAddress>

Server::Server(QObject *parent): QTcpServer(parent),
	_threadMutex(new QMutex(QMutex::Recursive)),
	_queueMutex(new QMutex()),
	_waitConn(new QQueue<qintptr>())
{
	QThreadPool::globalInstance()->setMaxThreadCount(Server::ThreadPoolSize);
}

Server::~Server()
{
	delete _threadMutex;
	delete _queueMutex;
	delete _waitConn;
}

void Server::startServer()
{

	/*
	for (int i=0; i<Server::ThreadPool; i++) {
		_threads = new ConnectionThread(i, this);
	}
	*/
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

	thread->start();
}
