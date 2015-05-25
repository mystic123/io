#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "global.h"
#include "server.h"

int main(int argc, char *argv[])
{


	QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

		 db.setHostName("localhost");
		 db.setDatabaseName("testdb");
		 db.setUserName("testusr");
		 db.setPassword("test");

		 if(!db.open())
		 {
			  qDebug() << "Database cannot be opened";
		 }

							 //Unitl here no errors

	QString consulta = "Insert into users values ('1','email@email.com','fname','lname','f');";


		 //db.transaction();

		 QSqlQuery query(db);
		 query.prepare(consulta);     //Here tried to pass directly the string with same results
		 query.exec();                //Even omitted .prepare but nothing
		 query.finish();


		 qDebug() << "Rows affected: " << query.numRowsAffected();

	QCoreApplication a(argc,argv);
	Server server;
	server.startServer();
	return a.exec();
}

