#include "client.h"



Client::Client(QObject *parent) : QObject(parent)
{

}

Client::~Client()
{

}

Event Client::getEventData(id_type id)
{
	 _socket = new QTcpSocket();
	 _socket->connectToHost("127.0.0.1", 10666);
    _socket->waitForConnected();

    qDebug() << _socket->state();
	 _st.setDevice(_socket);
	_st << MessCodes::login;
	 id_type id = 12;
	 _st << id;
	 _socket->flush();
_socket->waitForBytesWritten();
	 _st << MessCodes::event_data;
	 _socket->flush();
	 qDebug() << "tu";
		id_type id2 = 14;
	 _st << id2;
	 _socket->flush();
	 qDebug() << "t2u";

	 Event e = Event::readEvent(_socket);
 qDebug() << "tu3";
		qDebug() << e.desc() << e.id() << e.attending() << e.founder() << e.invited();
	 qDebug() << "w f:" + e.desc() + " id: " + QString::number(e.id());
	 return e;

//    QStringList dataList;
//    dataList.append("Item 1");
//    dataList.append("Item 2");
//    dataList.append("Item 3");
//    dataList.append("Item 4");
//    dataList.append("Item 5");
//    return dataList;
}

void Client::test()
{
	qDebug() << "signal" ;
	Event e;
	//_socket->waitForReadyRead();
	_st >> e;
qDebug() << "tu3";
	  qDebug() << e.desc() << e.id();
	qDebug() << "w f:" + e.desc() + " id: " + QString::number(e.id());
}
