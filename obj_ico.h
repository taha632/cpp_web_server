#ifndef OBJ_ICO_H
#define OBJ_ICO_H

#include <QObject>
#include <QTcpSocket>
#include <string.h>


using namespace std;

class obj_ico : public QObject
{
    Q_OBJECT
public:
    explicit obj_ico(QObject *parent = 0);

    QByteArray ico_content();


signals:

public slots:
};

#endif // OBJ_ICO_H
