#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



    /* TODO:
     * Bevor ich das main-window öffne, möchte ich ein Dialog erstellen, der benutzer-credentials abfragt.
     * */

    // Bevor der erste Dialog gezeigt wird, möchte ich die dementsprechenden Signale und Slots mit den Steuerungselementen verbinden
    w.connectWidgets();


    w.show();

    return a.exec();
}
