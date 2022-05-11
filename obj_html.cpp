#include "obj_html.h"

obj_html::obj_html(QObject *parent) : QObject(parent)
{

}

QByteArray obj_html::html_content()
{
    QByteArray entete("HTTP/1.1 200 OK\r\n Content-Type: text/html;");
    return entete;
}
