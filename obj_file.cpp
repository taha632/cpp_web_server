#include "obj_file.h"
#include <QDebug>
#include "path.h"

obj_File::obj_File(QObject *parent) : QObject(parent)
{}




void obj_File::setFileName(string name)
{
    filename = name;
}
void obj_File::setFileExtenison()
{
    int point_occurence=filename.find(".");
    if(point_occurence!=-1)  extension=filename.substr(point_occurence,filename.length()-point_occurence);
}

void obj_File::setFileURL()
{
    QString str=QString::fromStdString(path+string(filename.c_str()));
    url=str;
}


void obj_File::create_Qfile(QString url)
{
    qfile = new QFile(url);
}
