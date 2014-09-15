#include "BracketMatch.h"

BracketMatch::BracketMatch(quint8 matchNumber, QObject *parent) :
    QObject(parent), m_matchNumber(matchNumber), m_team1(nullptr), m_team2(nullptr)
{
}

Team* BracketMatch::team1() {
    return m_team1;
}

void BracketMatch::setTeam1(Team *team) {
    m_team1 = team;
    team1Changed(m_team1);
}

Team* BracketMatch::team2() {
    return m_team2;
}

void BracketMatch::setTeam2(Team *team) {
    m_team2 = team;
    team2Changed(m_team2);
}
