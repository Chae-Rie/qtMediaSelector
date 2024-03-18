#include "mainwindow.h"
#include "credentialdialog.h"
#include "dbmanager.h"
#include "helperfunction.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainDialog;

    // Initialisierung der SQLite-Datenbank
    DbManager SqlLiteDatabase;
    SqlLiteDatabase.Connect();
    SqlLiteDatabase.CreateMainTables();
    /* Der MainDialog muss aufjedenfall erstellt worden sein,
     * da im Zuge seiner Erstellung auch die verschiedenen Widgets erstellt werden, die es braucht
     * um irgendwas in dem Dialog zu nutzen, als auch die Verbindung zur Datenbank wird dann erst ermöglicht.
     */

    mainDialog.Login(SqlLiteDatabase);




    /* TODO:
     * Wie komme ich denn zuverlässig an Graphen? Gibt es dazu auch ein passendes API?
     * Vielleicht unter QT? Wo platziere ich den button für die Graphen?
     */

    // TODO: Ich kann den MainDialog beim Logout nicht einfach minimieren, er geht dann einfach aus, weil


    mainDialog.show();

    return app.exec();
}
