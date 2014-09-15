#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include <QObject>
#include <QDebug>
#include "FreeBracketServer.h"

class ApplicationData : public QObject
{
    Q_OBJECT
public:
    ApplicationData() { }

    Q_INVOKABLE void startServer() {
        qDebug() << "starting server...";

        QString ipAddress = "127.0.0.1";
        quint16 port = 1337;

        m_server = new FreeBracketServer(this);

        bool success = m_server->listen(QHostAddress(ipAddress), port);
        if(!success)
        {
            qFatal("Could not listen.");
        }

        qDebug() << "Ready on " << ipAddress << " at port " << port;
    }


private:
    FreeBracketServer *m_server;

private slots:

};

#endif // APPLICATIONDATA_H
