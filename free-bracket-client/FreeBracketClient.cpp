#include <QHostAddress>

#include "FreeBracketClient.h"
#include "FreeBracketCommands.h"



FreeBracketClient::FreeBracketClient(Bracket *bracket, QObject *parent) :
    QObject(parent), m_bracket(bracket)
{
}


void FreeBracketClient::connectToServer(QString host, quint16 port) {
    qDebug() << "Connecting to server...";
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    tcpSocket->abort();
    tcpSocket->connectToHost(QHostAddress(host), port);
}


void FreeBracketClient::connected()
{
    qDebug() << "Connected, getting history.";
    sendMessage(FreeBracketCommands::HISTORY_REPLAY);
}


void FreeBracketClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "RemoteHostClosedError";
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "HostNotFoundError";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "ConnectionRefusedError";
        break;
    default:
        qDebug() << "Error: " << tcpSocket->errorString();
    }
}

void FreeBracketClient::readMessage()
{
    QString msg;
    QStringList lines;
    while(tcpSocket->canReadLine())
    {
        msg = QString::fromUtf8(tcpSocket->readLine()).trimmed();
        lines = msg.split("/n");
        for(QString line : lines) {
            parseMessage(line);
        }
    }
}





void FreeBracketClient::parseMessage(QString msg) {
    qDebug() << "Received: " << msg;

    int delimit = msg.indexOf(":");
    QString command = msg.mid(0, delimit);
    QString payload = msg.mid(delimit+1, msg.length() - delimit);


    if(command == FreeBracketCommands::TEAMS_ADD) {
        m_bracket->addTeam(Team::deserialize(payload, this));
    } else if(command == FreeBracketCommands::TEAMS_DELETE) {
        quint8 id = payload.toInt();
        qDebug() << "Deleting team: " << id;
        m_bracket->deleteTeam(id);
    } else if(command == FreeBracketCommands::BRACKET_START) {
        qDebug() << "Starting tournament.";
        m_bracket->startTournament();
    } else {
        qDebug() << "Unknown Command: " << msg;
    }
}

void FreeBracketClient::addTeam(QString name) {
    sendMessage(FreeBracketCommands::TEAMS_ADD + ":" + name);
}

void FreeBracketClient::deleteTeam(quint8 id) {
    sendMessage(FreeBracketCommands::TEAMS_DELETE + ":" + QString::number(id));
}

void FreeBracketClient::startTournament() {
    sendMessage(FreeBracketCommands::BRACKET_START);
}

void FreeBracketClient::sendMessage(QString msg) {
    tcpSocket->write(QString(msg + "\n").toUtf8());
}
