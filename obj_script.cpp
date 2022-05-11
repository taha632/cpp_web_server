#include "obj_script.h"
#include "path.h"


obj_script::obj_script(QObject *parent) : QObject(parent)
{

}

QByteArray obj_script::script(QString url,string extension)
{
    QByteArray rep=NULL;

    if(extension==".py")
    {
        qDebug()<<"url :"<<url;
        rep="Ceci est un fichier python dont l'executable est le suivant :\n\n\n";

        string commande("python "+url.toStdString()+ " > /home/debian/PROG_C++/mon_serveur/public_html/output_python.txt");
        system(commande.c_str());

        QString ch=QString::fromStdString(path+string("/output_python.txt"));
        QFile *Myfile=new QFile(ch);
        if (!Myfile->open(QIODevice::ReadOnly))
        {
            delete Myfile;
            return NULL;
        }
        rep=rep+Myfile->readAll();
        Myfile->close();
        system("rm output_python.txt");
    }
    else if(extension==".sh")
    {
        rep="Ceci est un fichier shell dont l'executable est le suivant :\n\n\n";

        string STR = url.toStdString();
        int p=STR.find("/");
        for(int i=0;i<5;i++)
        {
            STR=STR.substr(p+1, STR.length()-p);
            p=STR.find("/");
        }
        STR=STR.substr(p+1, STR.length()-p);
        string commande="./"+STR+" > "+path+"/output_shell.txt";
        system(commande.c_str());

        QString ch=QString::fromStdString(path+string("/output_shell.txt"));
        QFile *Myfile=new QFile(ch);
        if (!Myfile->open(QIODevice::ReadOnly))
        {
            delete Myfile;
            return NULL;
        }
        rep=rep+Myfile->readAll();
        Myfile->close();
        system("rm output_shell.txt");
    }
    else if(extension==".c")
    {
        rep="Ceci est un fichier C dont l'executable est le suivant :\n\n\n";

        string STR = url.toStdString();
        int p=STR.find("/");
        for(int i=0;i<5;i++)
        {
            STR=STR.substr(p+1, STR.length()-p);
            p=STR.find("/");
        }
        STR=STR.substr(p+1, STR.length()-p);

        string commande="gcc "+STR+" -o prog";
        system(commande.c_str());
        system("./prog > output_C.txt");

        QString ch=QString::fromStdString(path+string("/output_C.txt"));
        QFile *Myfile=new QFile(ch);
        if (!Myfile->open(QIODevice::ReadOnly))
        {
            delete Myfile;
            return NULL;
        }
        rep=rep+Myfile->readAll();
        Myfile->close();
        system("rm prog");
        system("rm output_C.txt");
    }

    return rep;
}
