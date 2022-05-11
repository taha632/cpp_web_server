#include "obj_dir.h"
#include "path.h"


obj_dir::obj_dir(QObject *parent) : QObject(parent)
{

}

void obj_dir::create_Qdir(QString url)
{
    qdir = new QDir(url);
}

void obj_dir::show_content(QString url,QByteArray *rep)
{
    obj_File mf;
    string commande("ls -ahrtpl "+url.toStdString()+ " > "+path+"/output_directory.txt");
    system(commande.c_str());


    QString ch = QString::fromStdString(path+string("/output_directory.txt"));
    mf.create_Qfile(ch);

    if (!mf.qfile->open(QIODevice::ReadOnly))
    {
        delete mf.qfile;
        return;
    }
    *rep=mf.qfile->readAll();
    mf.qfile->close();

    system("rm output_directory.txt");

}
