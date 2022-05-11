#ifndef OBJ_FILE_H
#define OBJ_FILE_H

#include <QObject>
#include <string.h>
#include <QFile>

using namespace std;

class obj_File : public QObject
{
    Q_OBJECT
public:
    explicit obj_File(QObject *parent = 0);

    string filename;
    string extension;
    QString url;
    int filesize;
    QFile* qfile;

    void create_Qfile(QString);
    void setFileName(string);
    void setFileExtenison();
    void setFileURL();
};

#endif // OBJ_FILE_H
