#include "obj_image.h"

obj_image::obj_image(QObject *parent) : QObject(parent)
{

}

QByteArray obj_image::image_content()
{
    QByteArray entete("HTTP/1.1 200 OK\r\n Content-Type: image/jpeg; charset=UTF-8\r\n\r\n");
    return entete;
}
