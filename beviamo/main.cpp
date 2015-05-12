#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVariant>
#include <QString>
#include <QtCore/QUrl>
#include <QtQml/QQmlContext>
#include <QtCore/QCommandLineOption>
#include <QGuiApplication>
#include <QtCore/QCommandLineParser>
#include <QStyleHints>
#include <QScreen>
#include "client.h"
#include "event.h"

#ifdef QT_WEBVIEW_WEBENGINE_BACKEND
#include <QtWebEngine>
#endif // QT_WEBVIEW_WEBENGINE_BACKEND

QObject *cpphack(QQmlApplicationEngine *engine)
{
    static Client *c = nullptr;
    if (!c) {
        c = new Client();
        c->setEngine(engine);
    }
    return c;
}

QObject *cpphack2(QQmlEngine *engine, QJSEngine *scriptengine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptengine)

    return cpphack(nullptr);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    #ifdef QT_WEBVIEW_WEBENGINE_BACKEND
        QtWebEngine::initialize();
    #endif // QT_WEBVIEW_WEBENGINE_BACKEND

    cpphack(&engine);

    const QString initialUrl = QStringLiteral("https://www.facebook.com/dialog/oauth?client_id=1615817788631871&redirect_uri=https://www.facebook.com/connect/login_success.html&response_type=token&scope=email,user_friends");
    engine.rootContext()->setContextProperty(QStringLiteral("initialUrl"), initialUrl);

    qmlRegisterSingletonType<Client>("Bev", 1, 0, "Client", cpphack2);
    qmlRegisterType<Event>("Bev", 1, 0, "Event");

    engine.load(QUrl(QStringLiteral("qrc:/qrc/main.qml")));

    return app.exec();
}
