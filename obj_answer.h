
#ifndef OBJ_ANSWER_H
#define OBJ_ANSWER_H

#include <QObject>
#include <QTcpSocket>
#include <string.h>

using namespace std;

class obj_answer : public QObject
{
    Q_OBJECT
public:
    explicit obj_answer(QObject *parent = 0);

    QByteArray write_answer(QByteArray);
    void write_answerScript(QByteArray,string);
    static bool is_script;  //permet de le differencier du type html

    QByteArray reponseScript;

};

#endif // OBJ_ANSWER_H
