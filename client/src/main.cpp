#include <QTcpSocket>
#include <QDebug>
#include <iostream>
#include "global.h"
#include "user.h"
#include "event.h"

using namespace std;

int main()
{
	QTcpSocket *socket = new QTcpSocket();
	QDataStream st(socket);
	socket->connectToHost("127.0.0.1",2040);
	socket->waitForConnected();

	if (socket->state() != QTcpSocket::ConnectedState) {
		qDebug() << "Error connecting. Is server running on localhost:2040?";
		return 0;
	}

	qint32 x;

	id_type id = 12;
	st << id;
	socket->flush();
	socket->waitForBytesWritten();

	qDebug() << "Test client";
	qDebug() << "Usage: 1 - get user data";
	qDebug() << "2 - get event data";
	qDebug() << "3 - get friends list";
	qDebug() << "4 - create event";

	while(cin>>x) {
		QByteArray data;
		switch(x) {
			case 1:
				qDebug()<< "Usage: " << "id of requested user";
				st << MessCodes::user_data;
				socket->flush();
				cin >> id;
				st << id;
				socket->flush();
				break;
			case 2:
				qDebug()<< "Usage: " << "id of requested event";
				st << MessCodes::event_data;
				socket->flush();
				cin >> id;
				st << id;
				socket->flush();
				break;
			case 3:
				qDebug()<< "Usage: " << "id of requested user's friends";
				st << MessCodes::friends_list;
				socket->flush();
				cin >> id;
				st << id;
				socket->flush();
				break;
			case 4:
				qDebug() << "Usage: " << "creator " << "description " << "friend_ids... (0 = end)";
				st << MessCodes::create_event;
				id_type creator;
				string desc;
				QList<id_type> invited;
				id_type id;
				cin >> creator >> desc;
				do {
					cin>>id;
					invited.push_back(id);
				} while (id != 0);
				Event e(creator, QString::fromStdString(desc), QDateTime(), invited);
				st << e;
				socket->flush();
				break;
		}
		socket->flush();
		socket->waitForReadyRead();

		User u;
		Event e;
		QList<id_type> l;
		switch(x) {
			case 1:
				st >> u;
				qDebug() << u.id() <<" "<<u.friends() << endl;
				break;
			case 2:
				st >> e;
				qDebug() << e.id() <<" "<< e.desc() <<" "<< e.date() <<" "<< e.invited() <<" "<< e.attending()<<endl;
				break;
			case 3:
				st >> l;
				qDebug() << l <<endl;
				break;
		}
	}
	return 0;
}
