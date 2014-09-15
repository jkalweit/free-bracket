#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ApplicationData.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ApplicationData data;
    engine.rootContext()->setContextProperty("appData", (QObject*)&data);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    data.startServer();

    return app.exec();
}
