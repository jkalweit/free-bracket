#ifndef BRACKET_H
#define BRACKET_H

#include <QObject>
#include <QQmlListProperty>
#include "Team.h"
#include "BracketRound.h"

class Bracket : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Team> teams READ teams NOTIFY teamsChanged)
    Q_PROPERTY(int numTeams READ numTeams NOTIFY numTeamsChanged)
    Q_PROPERTY(QQmlListProperty<BracketRound> rounds READ rounds NOTIFY roundsChanged)
    Q_PROPERTY(int numRounds READ numRounds NOTIFY numRoundsChanged)
public:
    //explicit Bracket(const Bracket &copy);
    explicit Bracket(QObject *parent = 0);

    QQmlListProperty<Team> teams();
    int numTeams();
    Team* addTeam(QString name);
    void addTeam(Team *team);
    void append_team(Team *team);
    Team* getTeamById(quint8 id);
    Team* getTeamAt(quint8 index);
    void deleteTeam(quint8 id);

    QQmlListProperty<BracketRound> rounds();
    int numRounds();

    void startTournament();

    Q_INVOKABLE void setWinner(quint8 round, quint8 match, quint8 team);

private:
    QList<Team *> m_teams;
    quint8 m_currId;
    void fireTeamsChanged();
    void fireRoundsChanged();

    QList<BracketRound *> m_rounds;

signals:
    void teamsChanged(QQmlListProperty<Team>);
    void numTeamsChanged(int);
    void roundsChanged(QQmlListProperty<BracketRound>);
    void numRoundsChanged(int);

public slots:

};

#endif // BRACKET_H
