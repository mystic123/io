#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qrc/main.qml")));

    Client c;

	 qDebug() << c.getEventData(14).desc();
    //engine.rootContext()->setContextProperty("myModel", QVariant::fromValue(cppClass.sendMessage()));
    //engine.rootContext()->setContextProperty("myModel", cppClass.sendMessage());

    return app.exec();
}
