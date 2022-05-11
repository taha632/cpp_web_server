#ifndef OBJ_ERROR_H
#define OBJ_ERROR_H

#include <QObject>
#include <string.h>
#include <QTcpSocket>
#include <QFile>
#include <QDir>



using namespace std ;
class obj_error : public QObject
{
    Q_OBJECT
public:
    explicit obj_error(QObject *parent = 0);

    QByteArray error404();
    QByteArray errorCmde();
    QByteArray errorAccess();

private:
    QByteArray error_detected(string fichier);
};

#endif // OBJ_ERROR_H
