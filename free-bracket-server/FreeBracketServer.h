#ifndef FREEBRACKETSERVER_H
#define FREEBRACKETSERVER_H

#include "SimpleServer.h"
#include "Bracket.h"

class FreeBracketServer : public SimpleServer
{
    Q_OBJECT
    public:
        FreeBracketServer(QObject *parent=0);

    protected:
        void handleMessage(QString msg, std::function<void (QString)> reply); //, QTcpSocket *client);

    private:
        Bracket *m_bracket;
        QStringList m_history;

        void addTeam(QString msg);
        void deleteTeam(QString msg);
        void startBracket();
        void replayHistory(std::function<void (QString)> reply);
};

#endif // FREEBRACKETSERVER_H
