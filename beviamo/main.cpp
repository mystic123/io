#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "cppclass.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    CppClass cppClass;

    //engine.rootContext()->setContextProperty("myModel", QVariant::fromValue(cppClass.sendMessage()));
    engine.rootContext()->setContextProperty("myModel", cppClass.sendMessage());

    return app.exec();
}
