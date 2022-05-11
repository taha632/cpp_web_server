

#ifndef FORTUNESERVER_H
#define FORTUNESERVER_H

#include <QStringList>
#include <QTcpServer>
#include <QtGlobal>
#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>
#include <QHostInfo>
#include <QObject>


class MySocketServer : public QTcpServer
{
Q_OBJECT

public:
        MySocketServer(QObject *parent = 0); //constructs a QTcpServer object
        int nb_requete;

protected:
    void incomingConnection(int socketDescriptor);
    /*its role is to add the socket to the list of
    pending incoming connections */
private:
};

#endif
