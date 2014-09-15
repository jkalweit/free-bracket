#ifndef TEAM_H
#define TEAM_H

#include <QObject>

class Team : public QObject
{
    Q_OBJECT    
    Q_PROPERTY(quint8 id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
public:
    explicit Team(const Team &t);
    explicit Team(quint8 id = 0, QString name = "", QObject *parent = 0);

    quint8 id();
    void setId(quint8 id);

    QString serialize();
    static Team* deserialize(QString serialized, QObject *parent);

private:
    quint8 m_id;
    QString m_name;

signals:
    void idChanged(quint8);
    void nameChanged(QString);

public slots:

};

#endif // TEAM_H
