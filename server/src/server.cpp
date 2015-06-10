#include "server.h"
#include "connectionthread.h"
#include <QHostAddress>

const int Server::threadCount = QThread::idealThreadCount();

Server::Server(QObject *parent): QTcpServer(parent), threads(), queue_mutex(), connection_waiting(), waiting_connections()
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

	for (int i = 0; i < threadCount; i++) {
		ConnectionThread *t = new ConnectionThread(this, i, connection_waiting);
		threads.push_back(t);
		connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));
		t->start();
	}
}

void Server::incomingConnection(qintptr socket_desc)
{
	qDebug()<<socket_desc<<"Connecting...\n";

	queue_mutex.lock();
	waiting_connections.push_back(socket_desc);
	queue_mutex.unlock();

	connection_waiting.wakeOne();
}

qintptr Server::nextClient()
{
	qintptr result;
	queue_mutex.lock();
	result = waiting_connections.takeFirst();
	queue_mutex.unlock();
	return result;
}

bool Server::clientWaiting()
{
	bool result;
	queue_mutex.lock();
	result = waiting_connections.empty();
	queue_mutex.unlock();
	return !result;
}
