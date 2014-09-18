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

    int delimit = msg.indexOf(":");
    QString command = msg.mid(0, delimit);
    QString payload = msg.mid(delimit+1, msg.length() - delimit);

    if(command == FreeBracketCommands::TEAMS_ADD) {
        addTeam(payload);
    } else if(command == FreeBracketCommands::TEAMS_DELETE) {
        deleteTeam(payload);
    } else if(command == FreeBracketCommands::BRACKET_START) {

        quint8 rounds = 1;

        // find required number of rounds
        while(exp2(rounds) < m_bracket->numTeams()) {
            rounds++;
        }

        quint8 byesRequired = exp2(rounds) - m_bracket->numTeams();

        // fill in byes
        qDebug() << "Teams required: " << exp2(rounds) << " Teams: " << m_bracket->numTeams() << " Byes Required: " << byesRequired;
        for(int i = 0; i < byesRequired; i++) {
            qDebug() << "Adding bye.";
            addTeam("bye");
        }

        startBracket();
    } else if(command == FreeBracketCommands::HISTORY_REPLAY) {
        replayHistory(reply);
    }
}

void FreeBracketServer::addTeam(QString msg) {
    Team *team = m_bracket->addTeam(msg);
    qDebug() << "Add Team: " << team->serialize();
    QString command = FreeBracketCommands::TEAMS_ADD + ":" + team->serialize();
    m_history.append(command);
    broadcast(command);
}

void FreeBracketServer::deleteTeam(QString msg) {
    qDebug() << "Delete Team";
    quint8 id = msg.toInt();
    m_bracket->deleteTeam(id);
    QString command = FreeBracketCommands::TEAMS_DELETE + ":" + QString::number(id);
    m_history.append(command);
    broadcast(command);
}

void FreeBracketServer::startBracket() {
    qDebug() << "Starting bracket.";
    QString command = FreeBracketCommands::BRACKET_START + ":" + "";
    m_history.append(command);
    broadcast(command);
}

void FreeBracketServer::replayHistory(std::function<void (QString)> reply) {
    qDebug() << "Sending history replay.";
    // construct one message to preserve order
    QString replyMsg = "";
    for(QString history : m_history) {
        qDebug() << "History item: " + history;
        replyMsg += history + "/n";
    }

    reply(replyMsg);
}
