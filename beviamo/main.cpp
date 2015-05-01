#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVariant>
#include <QString>
#include "client.h"
#include "event.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qrc/main.qml")));

    Client c;
    c.setEngine(&engine);
    c.login();

    //qmlRegisterType<Event>("Bev", 1, 0, "Event");

    return app.exec();
}
