#include "connectionthread.h"

ConnectionThread::ConnectionThread(qintptr ID, QObject *parent) : QThread(parent), socket_desc(ID)
{

}

ConnectionThread::~ConnectionThread()
{

}

void ConnectionThread::run()
{
	qDebug()<<"Thread started\n";

	socket = new QTcpSocket();

	if (!socket->setSocketDescriptor(this->socket_desc)) {
		emit error(socket->error());
		return;
	}
`
	connect(this->socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
	connect(this->socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

	qDebug()<<socket_desc<<"Client connected\n";

	exec();
}

void ConnectionThread::readyRead()
{
	QByteArray data = socket->readAll();

	qDebug()<<socket_desc<<"Data in: "<<data;

	socket->write(data);
}

void ConnectionThread::disconnected()
{
	qDebug() << socket_desc << " Disconnected"; socket->deleteLater();				exit(0);
}