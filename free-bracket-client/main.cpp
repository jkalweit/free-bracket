#include <QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>
#include <QObject>
#include "ApplicationData.h"
#include "Team.h"
#include "Bracket.h"

//Q_DECLARE_METATYPE(Team)


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Team>("FreeBracket", 1, 0, "Team");
    qmlRegisterType<Bracket>("FreeBracket", 1, 0, "Bracket");
    qmlRegisterType<BracketRound>("FreeBracket", 1, 0, "BracketRound");
    qmlRegisterType<BracketMatch>("FreeBracket", 1, 0, "BracketMatch");

    Bracket bracket;
    FreeBracketClient client(&bracket);





    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("client", (QObject*)&client);
    engine.rootContext()->setContextProperty("bracket", (QObject*)&bracket);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    client.connectToServer("127.0.0.1", 1337);

    return app.exec();


}
