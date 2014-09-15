#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include <math.h>
#include <vector>
#include <QObject>
#include <QList>
#include <QQmlListProperty>
#include <QStringList>
#include <QLine>
#include <QPoint>
#include <QDebug>
#include <QColor>
#include <QTcpSocket>
#include <QHostAddress>
#include <QAbstractSocket>

#include "FreeBracketClient.h"
#include "FreeBracketCommands.h"


class LineModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint16 x1 READ x1 WRITE setX1 NOTIFY x1Changed)
    Q_PROPERTY(qint16 y1 READ y1 WRITE setY1 NOTIFY y1Changed)
    Q_PROPERTY(qint16 x2 READ x2 WRITE setX2 NOTIFY x2Changed)
    Q_PROPERTY(qint16 y2 READ y2 WRITE setY2 NOTIFY y2Changed)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
public:
    LineModel(QPoint p1, QPoint p2)
        : LineModel(p1.x(), p1.y(), p2.x(), p2.y()) { }
    LineModel(qint16 x1, qint16 y1, qint16 x2, qint16 y2) :
        m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_color("transparent") { }

    qint16 x1() { return m_x1; }
    qint16 y1() { return m_y1; }
    qint16 x2() { return m_x2; }
    qint16 y2() { return m_y2; }
    QString color() { return m_color; }

    void setX1(qint16 x) {
        m_x1 = x;
        x1Changed(m_x1);
    }
    void setY1(qint16 y) {
        m_y1 = y;
        y1Changed(m_y1);
    }
    void setX2(qint16 x) {
        m_x2 = x;
        x2Changed(m_x2);
    }
    void setY2(qint16 y) {
        m_y2 = y;
        y2Changed(m_y2);
    }
    void setColor(QString color) {
        m_color = color;
        colorChanged(m_color);
    }

private:
    qint16 m_x1;
    qint16 m_y1;
    qint16 m_x2;
    qint16 m_y2;
    QString m_color;

signals:
    void x1Changed(qint16);
    void y1Changed(qint16);
    void x2Changed(qint16);
    void y2Changed(qint16);
    void colorChanged(QString);
};

class TeamModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(qint16 x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qint16 y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qint16 width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qint16 height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(bool isWinner READ isWinner WRITE setIsWinner NOTIFY isWinnerChanged)
public:
    TeamModel *nextTeam;
    TeamModel *opponentTeam;
    LineModel *line;

    TeamModel(const TeamModel &t)
        : TeamModel(t.m_id, t.m_name, t.m_x, t.m_y, t.m_width, t.m_height) {}
    TeamModel(qint8 id = 0, QString name = "", qint16 x = 0, qint16 y = 0, qint16 width = 0, qint16 height = 0) :
        nextTeam(nullptr), opponentTeam(nullptr), m_id(id), m_name(name), m_x(x), m_y(y), m_width(width), m_height(height), m_isWinner(false)  { }

    quint8 id() { return m_id; }
    QString name() { return m_name; }
    qint16 x() { return m_x; }
    qint16 y() { return m_y; }
    qint16 width() { return m_width; }
    qint16 height() { return m_height; }
    bool isWinner() { return m_isWinner; }

    QPoint lineStart() { return QPoint(m_x + m_width, m_y + (m_height / 2)); }
    QPoint lineEnd() { return QPoint(m_x, m_y + (m_height / 2)); }

    //Q_INVOKABLE void setWinner() { setIsWinner(true); }
    Q_INVOKABLE QObject* getNextTeam() const { return nextTeam; }

    void setId(quint8 id) {
        m_id = id;
        idChanged(m_id);
    }

    void setName(QString name) {
        m_name = name;
        nameChanged(m_name);
    }

    void setX(qint16 x) {
        m_x = x;
        xChanged(m_x);
    }

    void setY(qint16 y) {
        m_y = y;
        yChanged(m_y);
    }

    void setWidth(qint16 width) {
        m_width = width;
        widthChanged(m_width);
    }

    void setHeight(qint16 height) {
        m_height = height;
        heightChanged(m_height);
    }

    void setIsWinner(bool isWinner) {
        if(isWinner != m_isWinner) {
            m_isWinner = isWinner;
            isWinnerChanged(m_isWinner);

            if(m_isWinner) {
                if(opponentTeam) opponentTeam->setIsWinner(false);
                if(nextTeam) nextTeam->setName(m_name);
                if(line) line->setColor("black");
            } else {
                if(nextTeam) nextTeam->setName("");
                if(line) line->setColor("transparent");
            }
        }
    }

private:
    quint8 m_id;
    QString m_name;
    qint16 m_x;
    qint16 m_y;
    qint16 m_width;
    qint16 m_height;
    bool m_isWinner;

signals:
    void idChanged(quint8);
    void nameChanged(QString);
    void xChanged(qint16);
    void yChanged(qint16);
    void widthChanged(qint16);
    void heightChanged(qint16);
    void isWinnerChanged(bool);
};

Q_DECLARE_METATYPE(TeamModel)


class MatchModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString team1 READ team1 WRITE setTeam1 NOTIFY team1Changed)
    Q_PROPERTY(QString team2 READ team2 WRITE setTeam2 NOTIFY team2Changed)
public:
    QString _team1;
    QString _team2;


    MatchModel(QString team1, QString team2) :
        _team1(team1), _team2(team2) { }

    QString team1() { return _team1; }
    void setTeam1(QString team1) {
        _team1 = team1;
        team1Changed(_team1);
    }

    QString team2() { return _team2; }
    void setTeam2(QString team2) {
        _team2 = team2;
        team2Changed(_team2);
    }

signals:
    void team1Changed(QString);
    void team2Changed(QString);
};

class RoundModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint8 round READ round WRITE setRound NOTIFY roundChanged)
public:
    QList<QObject *> teams;
    RoundModel(qint8 round)
        : m_round(round) {
    }

    qint8 round() { return m_round; }
    void setRound(qint8 round) {
        if(m_round != round) {
            m_round = round;
            roundChanged(m_round);
        }
    }

    Q_INVOKABLE QList<QObject *> getTeams() const {
        return teams;
    }

private:
    qint8 m_round;    

signals:
    void roundChanged(qint8);
};


class ApplicationData : public QObject
{
    Q_OBJECT
public:
    ApplicationData()
    {
        //m_client = new FreeBracketClient();
    }


//    void createBracket() {

//        int numTeams = m_teams.size();

//        QList<QString> names;
//        for(int i = 0; i < numTeams; i++) {
//            names.append(QString("Team " + QString::number(i+1)));
//        }

//        // Requires at least 2 teams
//        if(numTeams < 2)
//            return;

//        int numRounds = 1;

//        //QList<QObject*> rounds;

//        int maxTeams = 2 * numRounds;
//        while(maxTeams < numTeams) {
//            numRounds++;
//            maxTeams = (uint) pow(2, numRounds);
//            //rounds.append(new Round(round));
//        }

//        int x = 10;
//        int y = 10;
//        int xoffset = 20;
//        int yoffset = 2;
//        int teamWidth = 150;
//        int teamHeight = 15;

//        int matchYOffset = 5;

//        qDebug() << "rounds: " << numRounds;

//        TeamModel *team1;
//        TeamModel *team2;

//        RoundModel *round = nullptr;
//        RoundModel *prevRound = nullptr;

//        for(int l = numRounds; l > 0; l--) {



//            prevRound = round;
//            round = new RoundModel(l);

//            //qDebug() << "   round: " << l;

//            int roundSize = pow(2, l);
//            for(int i = 0; i < roundSize; i+=2) {

//                if(prevRound) {
//                    int y1 = ((TeamModel*) prevRound->teams[i * 2])->y();
//                    int y2 = ((TeamModel*) prevRound->teams[(i * 2) + 2])->y();
//                    y = (y1 + y2) / 2;
//                }

//                team1 = new TeamModel(i, "", x, y, teamWidth, teamHeight);
//                team2 = new TeamModel(i + 1, "", x, y + teamHeight + yoffset, teamWidth, teamHeight);
//                team1->opponentTeam = team2;
//                team2->opponentTeam = team1;

//                if(l == numRounds) {

//                    //qDebug() << "debug: " << i/2 << ", " << i/2+(roundSize/2);
//                    if(i/2 < names.size()) {
//                        team1->setName(names[i/2]);
//                    }
//                    if(i/2+(roundSize/2) < names.size()) {
//                        team2->setName(names[i/2+(roundSize/2)]);
//                    }
//                }

//                round->teams.append(team1);
//                round->teams.append(team2);

//                y += (teamHeight * 2 + yoffset + matchYOffset);

//                if(prevRound) {
//                    TeamModel *prev1 = ((TeamModel*) prevRound->teams[i * 2]);
//                    TeamModel *prev2 = ((TeamModel*) prevRound->teams[(i * 2) + 1]);
//                    TeamModel *prev3 = ((TeamModel*) prevRound->teams[(i * 2) + 2]);
//                    TeamModel *prev4 = ((TeamModel*) prevRound->teams[(i * 2) + 3]);

//                    prev1->nextTeam = team1;
//                    prev2->nextTeam = team1;
//                    prev3->nextTeam = team2;
//                    prev4->nextTeam = team2;

//                    prev1->line = new LineModel(prev1->lineStart(), team1->lineEnd());
//                    prev2->line = new LineModel(prev2->lineStart(), team1->lineEnd());
//                    prev3->line = new LineModel(prev3->lineStart(), team2->lineEnd());
//                    prev4->line = new LineModel(prev4->lineStart(), team2->lineEnd());

//                    m_lines.append(prev1->line);
//                    m_lines.append(prev2->line);
//                    m_lines.append(prev3->line);
//                    m_lines.append(prev4->line);

//                }


//                //qDebug() << "       team: " << i;
//            }

//            x += teamWidth + xoffset;

//            m_rounds.append(round);
//        }
//    }



//    Q_INVOKABLE void connectToServer() {
//        m_client->connectToServer("127.0.0.1", 1337);
//    }

//    Q_INVOKABLE void addTeam(QString name) const {
//        qDebug() << "Adding team: " << name;
//        m_client->addTeam(name);
//        //tcpSocket->write(QString(FreeBracketCommands::TEAMS_ADD + ":" + name + "\n").toUtf8());
//    }

//    Q_INVOKABLE void deleteTeam(quint8 id) const {
//        qDebug() << "Deleting team: " << id;
//        m_client->deleteTeam(id);
//        //tcpSocket->write(QString(FreeBracketCommands::TEAMS_DELETE + ":" + QString::number(id) + "\n").toUtf8());
//    }


signals:

public slots:

private:    
//    FreeBracketClient *m_client;

};

#endif // APPLICATIONDATA_H
