#include "mainwindow.h"
#include "dbmanager.h"
#include "helperfunction.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



    /* TODO:
     * Bevor ich das main-window öffne, möchte ich ein Dialog erstellen, der benutzer-credentials abfragt.
     * */


    /* TODO:
     * Wie komme ich denn zuverlässig an Graphen? Gibt es dazu auch ein passendes API?
     * Vielleicht unter QT? Wo platziere ich den button für die Graphen?
     */

    // Initialisierung der SQLite-Datenbank
    DbManager SqlLiteDatabase;
    SqlLiteDatabase.Connect();
    SqlLiteDatabase.CreateMainTables();


    Datamanager::BOOK_CONTENT myExampleBookContainer;
    myExampleBookContainer.author = "moo",
    myExampleBookContainer.isbn = "1337347234";
    myExampleBookContainer.title = "ExampleTitle101";
    myExampleBookContainer.genre = "Thriller";
    myExampleBookContainer.publisher = "Hubert Burda Media AG";
    myExampleBookContainer.date = "1999-05-23";
    myExampleBookContainer.condition = "neuwertig";
    myExampleBookContainer.language = "Fujoneze";

    // SqlLiteDatabase.CreateNewRecord(myExampleBookContainer);

    Datamanager::MAGAZINE_CONTENT myExampleMagazineContainer;
    myExampleMagazineContainer.issn = "123-2343-45-4";
    myExampleMagazineContainer.title = "Russia Today";
    myExampleMagazineContainer.publisher = "Putins Mom";
    myExampleMagazineContainer.genre = "PropagandaShit";
    myExampleMagazineContainer.language = "Russkie jest";
    myExampleMagazineContainer.publishingRate = "monatlich";
    myExampleMagazineContainer.releaseDate = "1999-01-02";
    myExampleMagazineContainer.condtion = "starke Gebrauchsspuren";

    // SqlLiteDatabase.CreateNewRecord(myExampleMagazineContainer);

    Datamanager::OTHERS_CONTENT myExampleOthersContainer;
    myExampleOthersContainer.number = "102343042340234Z";
    myExampleOthersContainer.title = "Badminton-Set";
    myExampleOthersContainer.publisher = "XY Badminton Ltd.";
    myExampleOthersContainer.description = "2 Schläger, Farbe Schwarz, 1x Loch im Netz, abgegriffene Grifffläche";
    myExampleOthersContainer.condition = "abgenutzt";

    // SqlLiteDatabase.CreateNewRecord(myExampleOthersContainer);

    SqlLiteDatabase.PrintAllBooks();
    w.show();

    return a.exec();
}
