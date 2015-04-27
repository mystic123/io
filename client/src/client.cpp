#include "client.h"

Client::Client(): _socket(0), _st(0)
{	
}

Client::~Client()
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
