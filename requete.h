#ifndef REQUETE_H
#define REQUETE_H

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <QFile>
#include <QDir>
#include <QList>
#include <QTcpSocket>
using namespace std ;


class requete
{
public :
    requete();

    static QByteArray reponse;
    static string     concat;
    static QByteArray repSC;
    string GETrequete(QTcpSocket& tcpsocket);
    void traitement_req(string req,int n_c);

private:
    char tampon[65536];  // represente 16 bits en binaire
    static bool is_disabled;
    string removeEndLine(string s);

};










#endif // REQUETE_H
