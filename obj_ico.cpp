#include "obj_ico.h"

obj_ico::obj_ico(QObject *parent) : QObject(parent)
{

}

QByteArray obj_ico::ico_content()
{
    QByteArray entete("HTTP/1.1 200 OK\r\n Content-Type: image/vnd.microsoft.icon; charset=UTF-8\r\n\r\n");
    return entete;
}
