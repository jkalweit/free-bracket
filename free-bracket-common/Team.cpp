#include <QDebug>
#include <QStringList>
#include "Team.h"



Team::Team(const Team &t) :
    Team(t.m_id, t.m_name, t.parent())
{}

Team::Team(quint8 id, QString name, QObject *parent) :
    QObject(parent), m_id(id), m_name(name)
{}


quint8 Team::id() { return m_id; }
void Team::setId(quint8 id) {
    if(id != m_id) {
        m_id = id;
        idChanged(m_id);
    }
}


QString Team::serialize() {
    //qDebug() << "          test4: " << m_id << ", " << m_name;
    return QString::number(m_id) + ":" + m_name;
}

Team* Team::deserialize(QString serialized, QObject *parent)
{
    QStringList split = serialized.split(":");

    quint8 id = split[0].toInt();
    QString name = split[1];

    Team *t = new Team(id, name, parent);
//    qDebug() << "    test2: " << id << ", " << name << ": " << t->serialize();
    return t;
}
