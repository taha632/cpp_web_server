#ifndef OBJ_IMAGE_H
#define OBJ_IMAGE_H

#include <QObject>
#include <QTcpSocket>
#include <string.h>


using namespace std;

class obj_image : public QObject
{
    Q_OBJECT
public:
    explicit obj_image(QObject *parent = 0);

    QByteArray image_content();


signals:

public slots:
};

#endif // OBJ_IMAGE_H
