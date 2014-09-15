#ifndef BRACKETROUND_H
#define BRACKETROUND_H

#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include "BracketMatch.h"

class BracketRound : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 round MEMBER m_round NOTIFY roundChanged)
    Q_PROPERTY(quint8 size MEMBER m_size NOTIFY sizeChanged)
    Q_PROPERTY(QQmlListProperty<BracketMatch> matches READ matches NOTIFY matchesChanged)
public:
    explicit BracketRound(quint8 round = 0, quint8 size = 0, QObject *parent = 0);
    QQmlListProperty<BracketMatch> matches();
    quint8 numMatches();

    void setTeam(quint8 number, Team* team);
    BracketMatch* getMatchByMatchNumber(quint8 matchNumber);

private:
    quint8 m_round;
    quint8 m_size;
    QList<BracketMatch *> m_matches;

signals:
    void roundChanged(quint8);
    void sizeChanged(quint8);
    void matchesChanged(QQmlListProperty<BracketMatch>);    

public slots:

};

#endif // BRACKETROUND_H
