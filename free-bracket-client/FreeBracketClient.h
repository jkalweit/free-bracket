#ifndef FREEBRACKETCLIENT_H
#define FREEBRACKETCLIENT_H

#include <QObject>
#include <QQmlListProperty>
#include <QTcpSocket>
#include "Team.h"
#include "Bracket.h"

class FreeBracketClient : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(Bracket bracket MEMBER m_bracket NOTIFY bracketChanged)
public:
    explicit FreeBracketClient(Bracket *bracket, QObject *parent = 0);
    //QQmlListProperty<Team> teams();

    Q_INVOKABLE void connectToServer(QString host, quint16 port);
    Q_INVOKABLE void startTournament();

    Q_INVOKABLE void addTeam(QString name);
    Q_INVOKABLE void deleteTeam(quint8 id);

    //Q_INVOKABLE Bracket* getBracket();

private:
    QTcpSocket *tcpSocket;
    Bracket *m_bracket;
    void sendMessage(QString msg);
    void parseMessage(QString msg);

signals:
    //void bracketChanged(Bracket);

public slots:
    void connected();
    void displayError(QAbstractSocket::SocketError socketError);
    void readMessage();

};

#endif // FREEBRACKETCLIENT_H
