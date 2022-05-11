

#include "requete.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>

#include "obj_file.h"
#include "obj_dir.h"
#include "obj_script.h"
#include "obj_image.h"
#include "obj_ico.h"
#include "obj_html.h"

#include "path.h"

QList<string> List_req; //Contient La liste des requetes ; une sorte d'historique

int nb_d_erreurs=0;
int nb_req=0;
int nb_d_erreurs_404=0;
int nb_d_erreurs_acces=0;
int nb_d_erreurs_file_size_0=0;
int nb_d_erreurs_cmde=0;




requete::requete()
{}

bool requete::is_disabled=false;
QByteArray requete::reponse=NULL;
QByteArray requete::repSC=NULL;
string requete::concat;

string requete::removeEndLine(string s)
{
    while( s.at(s.length()-1) == '\r' ||
                    s.at(s.length()-1) == '\n' ){
            s = s.substr(0, s.length()-1);
    }
    return s;
}

string requete::GETrequete(QTcpSocket& tcpSocket)
{
    int lineLength = tcpSocket.readLine(tampon, 65536);
    string ligne( tampon );
    ligne = removeEndLine( ligne );
    nb_req++;

    List_req.append(ligne);
    return ligne;
}

void requete::traitement_req(string req,int n_c)
{

    cout << "requete : =>" << req << "<=" << endl;
    int pos1 = req.find(" "); //premiere occurence = 3
    string cmde = req.substr(0, pos1);

    if(cmde !="GET" && cmde!="EXIT")
    {
        reponse="err_cmde";
        nb_d_erreurs_cmde++;
        nb_d_erreurs++;
    }
    else if(cmde=="EXIT")
    {
        reponse="\n-----You are Exiting-----\n\n";
    }

    else
    {
        req = req.substr(pos1+1, req.length()-pos1);
        cout << "1. : " << cmde  << endl;
        cout << "2. : " << req << endl;
        int pos2 = req.find(" ");
        string file = req.substr(0, pos2);
        req = req.substr(pos2+1, req.length()-pos2);
        cout << "3. : " << file  << endl;
        cout << "4. : '" << req << "'" << endl;

        obj_File mf;
        obj_dir md;

        mf.setFileName(file);
        mf.setFileExtenison();
        mf.setFileURL();

        mf.create_Qfile(mf.url);
        md.create_Qdir(mf.url);

        cout << " - Chemin du fichier : " << mf.url.toStdString() << endl;
        cout << " - isFile :          : " << mf.qfile->exists() << endl;
        cout << " - isDirectory       : " << md.qdir->exists() << endl;

        if (is_disabled == true )
        {
            reponse="Service desactivated";
        }

        if( mf.qfile->exists() == false &&  md.qdir->exists() == false )
        {
            repSC=NULL;
            if(mf.url.toStdString()==path+string("/private/desactivate.html"))
            {
                reponse="Service desactivated";
                is_disabled = true;
            }
            if(mf.url.toStdString()==path+string("/private/activate.html"))
            {
                reponse="Service re-activated";
                is_disabled = false;
            }
            else if(mf.url.toStdString() == path+string("/private"))
            {
                if (is_disabled == true )   return;

                reponse="HTTP/1.1 200 OK\r\n Content-Type: text/html;\n"
                        "<!DOCTYPE html>\n<html>\n<head>\n\t<meta charset=\"utf-8\">\n\t<title>private</title>\n</head>\n\n"
                        "<body>\n"
                        "<br><p style=\"font-size:17px;font-family:\'Roboto\',sans-serif;\">Cette section privee contient des informations sur :</p><br>"
                        "<p style=\"font-size:15px;font-family:\'Roboto\',sans-serif;\">- l'identite du serveur que vous pouvez acceder depuis la page <span style=\"color: red;\">\"\/info.private\"</span></p>"
                        "<p style=\"font-size:15px;font-family:\'Roboto\',sans-serif;\">- Les statistiques d'utilisation que vous pouvez acceder depuis la page <span style=\"color: red;\">\"\/statistiques.html\"</span></p>"
                        "<p style=\"font-size:15px;font-family:\'Roboto\',sans-serif;\">- Elle permet aussi d'activer et desactiver la reponse du serveur via les pages :<span style=\"color: red;\">\"\/activate.html\"</span> et <span style=\"color: red;\">\"\/desactivate.html\"</span></p><br>"
                        "</body></html>";

            }

            else if(mf.url.toStdString() == path+string("/private/info.private"))
            {
                if (is_disabled == true )   return;

                string date ="Date de compilation   : " + string(__DATE__);
                string time ="Heure de compilation  : " + string(__TIME__);

                QByteArray info="\n\tCette page contient des informations sur le serveur\n\n\n\n"
                                "Les Concepteurs : \n \t\t  "
                                "ELQANDILI Taha \n \t\t  BENAMAR Mohamed\n\n\n\n";
                QByteArray jump="\n\n";

                reponse=info+date.c_str()+jump+time.c_str();

            }
            else if(mf.url.toStdString()==path+string("/private/statistiques.html"))
            {
                if (is_disabled == true )   return;

                string req="<p style=\"font-size:17px;font-family:\'Roboto\',sans-serif;\">Le nombre de requetes recues : "+to_string(nb_req)+"<br><br></p>";
                string erreurs  ="\<br><br><p style=\"font-size:17px;font-family:\'Roboto\',sans-serif;\">Le nombre d'erreurs est : "+to_string(nb_d_erreurs)+"<br><br></p>";
                string err_404  ="- Erreurs 404          : "   +to_string(nb_d_erreurs_404)+"<br>";
                string err_acces="- Erreurs d'acces      : "   +to_string(nb_d_erreurs_acces)+"<br>";
                string err_size ="- Erreurs de taille    : "   +to_string(nb_d_erreurs_file_size_0)+"<br>";
                string err_cmde ="- Erreurs de commande  : "   +to_string(nb_d_erreurs_cmde)+"<br><br>";
                string nb_de_clients = "<p style=\"font-size:17px;font-family:\'Roboto\',sans-serif;\">Le nombre de clients est : "+to_string(n_c)+"<br><br></p>" ;

                reponse="HTTP/1.1 200 OK\r\n Content-Type: text/html;\n"
                        "<!DOCTYPE html>\n<html>\n<head>\n\t<meta charset=\"utf-8\">\n\t<title>private</title>\n</head>\n\n"
                        "<body>\n"
                        "<h2 style=\"font-size:25px;text-align:center;font-family:\'Roboto\',sans-serif;\">Cette page contient des informations sur les statistiques du serveur<h2><br>"
                        "<br>"+QByteArray(req.c_str(),req.length());

                QByteArray list;
                for(int i=0;i<List_req.length();i++)
                {
                    list="<p style=\"font-size:14px;font-family:\'Roboto\',sans-serif;margin-left:40px;color:#00400a88\">"
                         "\t*    "+QByteArray(List_req[i].c_str(),List_req[i].length())+"<br></p>";
                    reponse=reponse+list;
                }
                string Er=erreurs+"<p style=\"font-size:15px;font-family:\'Roboto\',sans-serif;margin-left:40px;color:#850000af\">"
                        +err_404+err_acces+err_size+err_cmde+"</p><br>";
               reponse=reponse+QByteArray(Er.c_str(),Er.length())+QByteArray(nb_de_clients.c_str(),nb_de_clients.length())+"</body>\n</html>";

            }

            else
            {
                if (is_disabled == true )   return;
                reponse="err_404";
                nb_d_erreurs_404++;
                nb_d_erreurs++;
            }
        }

        else if( md.qdir->exists() == true )
        {
            if (is_disabled == true )   return;
            md.show_content(mf.url,&reponse);
        }

        else if( mf.qfile->exists() == true )
        {
            if (is_disabled == true )   return;
            reponse=NULL;
            repSC=NULL;
            bool clear_rep=false;

            if(mf.extension==".py"||mf.extension==".c"||mf.extension==".sh")
            {
                reponse="Oscript";
                concat=mf.url.toStdString()+"|"+mf.extension; //permet de recuperer l'url et l'extension dans obj_answer
                clear_rep=true; //permet de ne pas recopier le contenu du fichier
            }
            else if(mf.extension==".png" || mf.extension==".jpg")
            {
                obj_image   objImage;
                reponse=objImage.image_content();
            }
            else if(mf.extension==".ico")
            {
                obj_ico     objIco;
                reponse=objIco.ico_content();
            }
            else if(mf.extension==".html")
            {
                reponse="Ohtml";
            }
            else    reponse=NULL;

            repSC=reponse; //pour la fonction write_script

            if(!clear_rep)
            {
                mf.create_Qfile(mf.url);
                if (!mf.qfile->open(QIODevice::ReadOnly))
                {
                    reponse="err_access";
                    nb_d_erreurs_acces++;
                    nb_d_erreurs++;

                    delete mf.qfile;
                    return;
                }
                reponse+=mf.qfile->readAll();
                mf.qfile->close();
            }
        }
    }
}


