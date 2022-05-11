#ifndef OBJ_DIR_H
#define OBJ_DIR_H

#include <QObject>
#include <string.h>
#include <QDir>

#include "obj_file.h"

using namespace std;

class obj_dir : public QObject
{
    Q_OBJECT
public:
    explicit obj_dir(QObject *parent = 0);

    QDir* qdir;
    void create_Qdir(QString);
    void show_content(QString,QByteArray*);

signals:

public slots:
};

#endif // OBJ_DIR_H
