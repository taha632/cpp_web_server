
#include "MySocketClient.h"

#include <QFileDialog>

QList<int> List_clients;
int len=0;

MySocketClient::MySocketClient(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{}


inline string removeEndLine(string s){
        while( s.at(s.length()-1) == '\r' ||
                        s.at(s.length()-1) == '\n' ){
                s = s.substr(0, s.length()-1);
        }
        return s;
}

int return_pos(QList<int> List,int val) //Il faut que les elements de la liste soit tous differents
{
    for(int i=0;i<List.length();i++)
    {
        if(List[i]==val)    return i;
    }
}

void MySocketClient::run()
{
    cout << "Starting MySocketClient::run()" << endl;
    tcpSocket = new QTcpSocket();


    if (!tcpSocket->setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket->error());
        return;
    }
    List_clients.append(socketDescriptor);

    for(int i=0;i<List_clients.length()-1;i++)
    {
        for(int j=i+1;j<List_clients.length();j++)
        {
            if(List_clients[i] == List_clients[j])  List_clients.removeAt(j);
        }
    }

    while (tcpSocket->bytesAvailable() < (int)sizeof(quint16)) {
        if (!tcpSocket->waitForReadyRead( 100000 )) {
                cout << "(EE) Erreur de time out !" << endl;
                return;
        }
    }

    bool cn=connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
    if(cn)
    {
        int pos=return_pos(List_clients,this->socketDescriptor);
        List_clients.removeAt(pos);
    }

    len=List_clients.length()+1;

    requete Req;
    obj_answer Answer;
    QByteArray repfinale;

    string la_requete=Req.GETrequete(*tcpSocket); // on recupere la requete
    Req.traitement_req(la_requete,len);  // On traite les erreurs , les fichiers scripts , ....

    Answer.write_answerScript(Req.repSC,Req.concat); //determine reponseScript
    if(Answer.is_script)    Req.reponse=NULL;
    repfinale=Answer.write_answer(Answer.reponseScript+Req.reponse);


    tcpSocket->write(repfinale);
    tcpSocket->disconnectFromHost();
    tcpSocket->waitForDisconnected();
    cout << "Finishing MySocketClient::run()" << endl;
}



void MySocketClient::disconnected()
{
    tcpSocket->deleteLater();
    exit(0);
}


