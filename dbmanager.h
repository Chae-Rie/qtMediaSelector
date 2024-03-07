#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QtSql/QSqlQueryModel> // Für die Abfrage von Inhalten aus der DB
#include <QSqlQuery>
#include "helperfunction.h"
#include "datamanager.h"

class DbManager
{
public:
    DbManager();
    virtual ~DbManager();

 // Methoden
    // Mithilfe der database-Funktion kann ich einen Pointer zu der erzeugten Datenbank bekommen.
    // laut der Doku, sollte ich keine Membervariable nutzen

    bool Connect();
    bool Disconnect();
    bool CreateMainTables();
    void PrintAllTables();
    bool PrintAllBooks();
    bool PrintAllMagazines();
    bool PrintAllOthers();

    bool CreateNewRecord(Datamanager::BOOK_CONTENT newContent);
    bool CreateNewRecord(Datamanager::MAGAZINE_CONTENT newContent);
    bool CreateNewRecord(Datamanager::OTHERS_CONTENT newContent);
// Attribute
private:
    QSqlDatabase m_database;

public:
    QString m_CurrentDate;

};

#endif // DBMANAGER_H
