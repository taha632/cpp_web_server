#ifndef OBJ_HTML_H
#define OBJ_HTML_H

#include <QObject>
#include <QTcpSocket>
#include <string.h>


using namespace std;

class obj_html : public QObject
{
    Q_OBJECT
public:
    explicit obj_html(QObject *parent = 0);

    QByteArray html_content();
};

#endif // OBJ_HTML_H
