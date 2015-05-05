#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVariant>
#include <QString>
#include "client.h"
#include "event.h"

QObject *dobra(QQmlApplicationEngine *engine)
{
    static Client *example = nullptr;
    if (!example) {
        example = new Client();
        example->setEngine(engine);
        example->login();
    }
    return example;
}

QObject *dobra2(QQmlEngine *engine, QJSEngine *scriptengine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptengine)

    return dobra(nullptr);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qrc/main.qml")));

    dobra(&engine);
    qmlRegisterSingletonType<Client>("Bev", 1, 0, "Client", dobra2);
    qmlRegisterType<Event>("Bev", 1, 0, "Event");

    return app.exec();
}
