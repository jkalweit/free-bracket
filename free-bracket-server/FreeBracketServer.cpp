#include "FreeBracketServer.h"

#include <QRegExp>
#include "FreeBracketCommands.h"
#include "Team.h"


FreeBracketServer::FreeBracketServer(QObject *parent)
    : SimpleServer(parent), m_bracket(new Bracket(this))
{
}

void FreeBracketServer::handleMessage(QString msg, std::function<void (QString)> reply) //, QTcpSocket *client)
{
    qDebug() << "Handling message in FreeBracketServer...";

    QStringList split = msg.split(":");
    if(split[0] == FreeBracketCommands::TEAMS_ADD) {        
        Team *team = m_bracket->addTeam(split[1]);
        qDebug() << "Add Team: " << team->serialize();
        QString command = FreeBracketCommands::TEAMS_ADD + ":" + team->serialize();
        m_history.append(command);
        broadcast(command);
    } else if(split[0] == FreeBracketCommands::TEAMS_DELETE) {
        qDebug() << "Delete Team";
        quint8 id = split[1].toInt();
        m_bracket->deleteTeam(id);
        QString command = FreeBracketCommands::TEAMS_DELETE + ":" + QString::number(id);
        m_history.append(command);
        broadcast(command);
    } else if(split[0] == FreeBracketCommands::TEAMS_GETALL) {
        qDebug() << "Sending teams: " << m_bracket->numTeams();
        Team *team;
        for(int i = 0; i < m_bracket->numTeams(); i++) {
            team = m_bracket->getTeamAt(i);
            QString replyMsg = QString(FreeBracketCommands::TEAMS_ADD + ":" + team->serialize());
            reply(replyMsg);
        }
    } else if(split[0] == FreeBracketCommands::BRACKET_START) {
        qDebug() << "Starting bracket.";
        QString command = FreeBracketCommands::BRACKET_START + ":" + "";
        m_history.append(command);
        broadcast(command);
    } else if(split[0] == FreeBracketCommands::HISTORY_REPLAY) {
        qDebug() << "Sending history replay.";
        // construct one message to preserve order
        QString replyMsg = "";
        for(QString history : m_history) {
            qDebug() << "History item: " + history;
            replyMsg += history + "/n";
        }

        reply(replyMsg);
    }
}


