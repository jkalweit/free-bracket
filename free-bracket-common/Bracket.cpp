#include "Bracket.h"

#include <QDebug>
#include <QtQml>
#include "Team.h"

//Bracket::Bracket(const Bracket &copy) :
//    Bracket(copy.parent())
//{
//}

Bracket::Bracket(QObject *parent) :
    QObject(parent), m_currId(0)
{
}

QQmlListProperty<Team> Bracket::teams() {
    return QQmlListProperty<Team>(this, m_teams);
}

int Bracket::numTeams() {
    return m_teams.size();
}

Team* Bracket::addTeam(QString name) {
    Team *team = new Team(m_currId++, name, this);
    addTeam(team);
    return team;
}

void Bracket::addTeam(Team *team) {
    m_teams.append(team);
    fireTeamsChanged();
}


Team* Bracket::getTeamById(quint8 id) {
    foreach(Team *team, m_teams) {
        if(team->id() == id) {
            return team;
        }
    }
    return 0;
}

Team* Bracket::getTeamAt(quint8 index) {
    return m_teams[index];
}

void Bracket::deleteTeam(quint8 id) {
    Team *team;
    for(int i = 0; i < m_teams.size(); i++) {
        team = m_teams[i];
        if(team->id() == id) {
            m_teams.removeAt(i);
            fireTeamsChanged();
            return;
        }
    }
}

void Bracket::fireTeamsChanged() {
    numTeamsChanged(numTeams());
    teamsChanged(teams());
}

void Bracket::fireRoundsChanged() {
    numRoundsChanged(numRounds());
    roundsChanged(rounds());
}

QQmlListProperty<BracketRound> Bracket::rounds() {
    return QQmlListProperty<BracketRound>(this, m_rounds);
}

int Bracket::numRounds() {
    return m_rounds.size();
}


void Bracket::startTournament() {

    m_rounds.clear();

    quint8 rounds = 1;

    // find required number of rounds
    while(exp2(rounds) < numTeams()) {
        rounds++;
    }

    // create rounds in typical bracket format, starting with biggest round first
    BracketRound *round;
    quint8 roundNumber = 1;

    BracketRound *firstRound = new BracketRound(roundNumber++, rounds, this);
    m_rounds.append(firstRound);

    for(int i = rounds - 1; i > 0; i--) {
        round = new BracketRound(roundNumber++, i, this);
        m_rounds.append(round);
    }

    // set teams for first round
    for(int i = 0; i < numTeams(); i++) {
        firstRound->setTeam(i, m_teams[i]);
    }

    fireRoundsChanged();
}

void Bracket::setWinner(quint8 round, quint8 match, quint8 team) {
    qDebug() << "setting winner: " << round << " " << match << " " << team;
    BracketRound *roundObj = m_rounds[round - 1];
    BracketMatch *matchObj = roundObj->getMatchByMatchNumber(match);
    qDebug() << "got match: " << matchObj->property("matchNumber").toUInt();
    Team *teamObj;
    if(team == 0)
        teamObj = matchObj->team1();
    else
        teamObj = matchObj->team2();

    if(teamObj == nullptr) {
        qDebug() << "No team to set as winner.";
        return;
    }

    match -= 1;
    int oddOffset = match % 2;
    BracketRound *nextRoundObj = m_rounds[round];
    quint8 nextMatchNumber = ((match-oddOffset) / 2) + 1;
    qDebug() << "next match number: " << nextMatchNumber;
    BracketMatch *nextMatchObj = nextRoundObj->getMatchByMatchNumber(nextMatchNumber);
    qDebug() << "got next match: " << nextMatchObj->property("matchNumber").toUInt();
    if(!oddOffset) {
        qDebug() << "Setting team1!";
        nextMatchObj->setTeam1(teamObj);
    } else {
        qDebug() << "Setting team2!";
        nextMatchObj->setTeam2(teamObj);
    }
}
