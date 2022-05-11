#ifndef OBJ_SCRIPT_H
#define OBJ_SCRIPT_H

#include <QObject>
#include <QTcpSocket>
#include <string.h>
#include <QFile>

using namespace std;

class obj_script : public QObject
{
    Q_OBJECT
public:
    explicit obj_script(QObject *parent = 0);


    QByteArray script(QString url,string extension);


signals:

public slots:
};

#endif // OBJ_SCRIPT_H
