#include <QCoreApplication>
#include <iostream>
#include "server.h"
#include "fbsync.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;

	 QCoreApplication a(argc,argv);
	 Server server;
	 server.startServer();
	 return a.exec();
}

