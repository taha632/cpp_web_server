
#include "obj_answer.h"

#include "obj_error.h"
#include "obj_html.h"
#include "obj_script.h"
//#include "requete.h"

#include <iostream>
#include <string.h>

using namespace std;

bool obj_answer::is_script;

obj_answer::obj_answer(QObject *parent) : QObject(parent)
{
    reponseScript=NULL;
}


QByteArray obj_answer::write_answer(QByteArray answer)
{
    obj_error   objErr;

    QByteArray inSocket=answer;

    //Gestion des erreurs
    if(answer=="err_404")
    {
        inSocket=objErr.error404();
        reponseScript=NULL;
    }
    else if(answer=="err_access")
    {
        inSocket=objErr.errorAccess();
        reponseScript=NULL;
    }
    else if(answer=="err_cmde")
    {
        inSocket=objErr.errorCmde();
        reponseScript=NULL;
    }

    else    inSocket=inSocket;

    return inSocket;

}


void obj_answer::write_answerScript(QByteArray answer,string concat)
{
    obj_html    objHtml;
    obj_script  objScript;

    if(answer=="Ohtml")
    {
        reponseScript=objHtml.html_content();
    }

    else if(answer=="Oscript")
    {
        is_script=true;

        string url;
        string ext;

        int p1=concat.find("|");
        url=concat.substr(0,p1);
        ext=concat.substr(p1+1,concat.length()-p1);
        QString Qurl=QString::fromStdString((url));

        reponseScript=objScript.script(Qurl,ext);
    }
    else
    {
        is_script=false;
        reponseScript=NULL;
    }
}
