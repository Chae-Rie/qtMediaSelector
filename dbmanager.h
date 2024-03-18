#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QtSql/QSqlQueryModel> // Für die Abfrage von Inhalten aus der DB
#include <QStandardItemModel>
#include <QSqlQuery>
#include "helperfunction.h"
#include "datamanager.h"
#include <QCoreApplication>

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
    bool PrintAllBooks();

    bool CreateNewRecord(Datamanager::BOOK_CONTENT newContent);
    bool CreateNewRecord(Datamanager::MAGAZINE_CONTENT newContent);
    bool CreateNewRecord(Datamanager::OTHERS_CONTENT newContent);
    bool CreateNewRecord(Datamanager::USER_CREDENTIALS newContent);

    bool QueryDbEntries(QSqlQueryModel* sqlModel, QString tableWithDelimiter);
    bool DeleteRecord(QString table, QString recordID);
    bool CheckUserCredentials(Datamanager::USER_CREDENTIALS givenCredentials);
    inline void SetRecordId(QString recordId){m_currentlySelectedRecordID = recordId;};
    inline QString GetRecordId(){return m_currentlySelectedRecordID;};

// Attribute
private:
    QSqlDatabase m_database;
    QString m_currentlySelectedRecordID; // Ermittelte ID aus der "Löschen"-Maske -> Angeklickter Eintrag
public:
    QString m_CurrentDate;

};

#endif // DBMANAGER_H
