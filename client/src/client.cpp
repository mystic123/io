#include "client.h"

Client::Client(): _socket(new QTcpSocket), _st(_socket)
{	
}

virtual Client::~Client()
{

}

void Client::connect() const
{
	_socket->connectToHost("127.0.0.1", 2040);
	_socket->waitForConnected();

	if (_socket->state() != QTcpSocket::ConnectedState) {
		qDebug() << "Error connecting. Is server running on localhost:2040?";
	}
}
