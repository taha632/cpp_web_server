#include "obj_error.h"
#include "path.h"

obj_error::obj_error(QObject *parent) : QObject(parent)
{}

QByteArray obj_error::error_detected(string f)
{
    QByteArray rep=NULL;
    QString str_error=QString::fromStdString(path+string("/error/")+f.c_str());
    QFile* file_err = new QFile(str_error);
    if (!file_err->open(QIODevice::ReadOnly))
    {
        delete file_err;
        return NULL;
    }
    rep=file_err->readAll();
    file_err->close();
    return rep;
}

QByteArray obj_error::error404()
{
    return error_detected("file_error_404.txt");
}

QByteArray obj_error::errorCmde()
{
    return error_detected("file_error_cmde.txt");
}

QByteArray obj_error::errorAccess()
{
    return error_detected("file_access.txt");
}
