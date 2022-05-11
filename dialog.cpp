
#include <QtGui>
#include <QtNetwork>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <stdlib.h>

#include "dialog.h"



Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    statusLabel = new QLabel;
    quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);



    if (!server.listen(QHostAddress::Any, 8079)) {
        QMessageBox::critical(this, tr("Small WEB Server"),
                              tr("Unable to start the server: %1.")
                              .arg(server.errorString()));
        close();
        return;
    }
    //Le serveur est lance a ce stade la
    //server.close();



    statusLabel->setText(tr("The server is running on port %1.\n"
                            "Use internet navigator now.")
                         .arg(server.serverPort()));

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    /*This function detects the click event on the button close and so
    it closes the window and stops the server
    */

    /*Ces deux fonctions permettent la mise en forme vercticale
    ou horizenrtale de la boite de dialogue
    */
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Small Web Server"));
}
