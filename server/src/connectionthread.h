#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class ConnectionThread : public QThread
{
	Q_OBJECT

public:
	explicit ConnectionThread(qintptr ID, QObject *parent = 0);
	~ConnectionThread();
	void run();

signals:
	void error(QTcpSocket::SocketError socketerror);

public slots:
	void readyRead();
	void disconnected();

private:
	QTcpSocket *socket;
	qintptr socket_desc;
};

#endif // CONNECTIONTHREAD_H
