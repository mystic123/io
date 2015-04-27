#ifndef CLIENT_H
#define CLIENT_H

#include "global.h"
#include "user.h"
#include "event.h"
#include <QTcpSocket>

class Client
{

public:
	Client();
	virtual ~Client();
	void connect() const;



private:
	QTcpSocket *_socket;
	QDataStream *_st;
};

#endif // CLIENT_H
