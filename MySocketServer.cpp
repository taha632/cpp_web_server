
#include "MySocketServer.h"
#include "MySocketClient.h"

#include <QDebug>
#include <stdlib.h>


MySocketServer::MySocketServer(QObject *parent)
    : QTcpServer(parent)
{
    this->nb_requete=0;
}

void MySocketServer::incomingConnection(int socketDescriptor)
{
    cout << socketDescriptor<<" - (II) Launching the Network monitor process" << endl;
    MySocketClient *thread = new MySocketClient(socketDescriptor, this);

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
    nb_requete++;
    cout << socketDescriptor<<" - (II) Network monitor process launch : OK" << endl;
}


