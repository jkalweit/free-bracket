#ifndef BRACKETMATCH_H
#define BRACKETMATCH_H

#include <QObject>
#include "Team.h"

class BracketMatch : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Team *team1 READ team1 WRITE setTeam1 NOTIFY team1Changed)
    Q_PROPERTY(Team *team2 READ team2 WRITE setTeam2 NOTIFY team2Changed)
    Q_PROPERTY(quint8 matchNumber MEMBER m_matchNumber NOTIFY matchNumberChanged)
public:
    explicit BracketMatch(quint8 matchNumber = 0, QObject *parent = 0);

    Team* team1();
    void setTeam1(Team *team);
    Team* team2();
    void setTeam2(Team *team);

private:
    quint8 m_matchNumber;
    Team* m_team1;
    Team* m_team2;    

signals:
    void team1Changed(Team*);
    void team2Changed(Team*);
    void matchNumberChanged(quint8);

public slots:

};

#endif // BRACKETMATCH_H
