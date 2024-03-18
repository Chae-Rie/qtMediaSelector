#include "testdatabasequeries.h"

void Testdatabasequeries::initTestCase()
{

}

void Testdatabasequeries::initTestCase_data()
{
    // Weil ich smart_pointer nutze, muss ich mich nicht um das Aufräumen kümmern
    m_dbmanager = std::make_unique<DbManager>();
    m_datamanager = std::make_unique<Datamanager>();





    // Beispielseintrag für vollständigen Bucheintrag
    m_bookContainer.author = "moo",
    m_bookContainer.isbn = "1337347234";
    m_bookContainer.title = "ExampleTitle101";
    m_bookContainer.genre = "Thriller";
    m_bookContainer.publisher = "Hubert Burda Media AG";
    m_bookContainer.date = "1999-05-23";
    m_bookContainer.condition = "neuwertig";
    m_bookContainer.language = "Fujoneze";

    // Beispielseintrag für vollständigen Magazineeintrag
    m_magazineContainer.issn = "123-2343-45-4";
    m_magazineContainer.title = "C't";
    m_magazineContainer.publisher = "Heise";
    m_magazineContainer.genre = "Informatik";
    m_magazineContainer.language = "Deutsch";
    m_magazineContainer.publishingRate = "monatlich";
    m_magazineContainer.releaseDate = "1999-01-02";
    m_magazineContainer.condtion = "starke Gebrauchsspuren";

    // Beispielseintrag für vollständigen Eintrag für andere Medien
    m_othersContainer.number = "102343042340234Z";
    m_othersContainer.title = "Badminton-Set";
    m_othersContainer.publisher = "XY Badminton Ltd.";
    m_othersContainer.description = "2 Schläger, Farbe Schwarz, 1x Loch im Netz, abgegriffene Grifffläche";
    m_othersContainer.condition = "abgenutzt";



    // -----
    // Set up database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:"); // In-memory database for testing
}

void Testdatabasequeries::cleanupTestCase()
{
    // Schließen der Verbindung
    QSqlDatabase::database().close();
}

void Testdatabasequeries::testTableCreation()
{
    QVERIFY(m_dbmanager.get()->CreateMainTables());
}

void Testdatabasequeries::testNewBookRecord()
{
    QVERIFY(m_dbmanager.get()->CreateNewRecord(m_bookContainer));
}

void Testdatabasequeries::testNewMagazineRecord()
{
    QVERIFY(m_dbmanager.get()->CreateNewRecord(m_magazineContainer));
}

void Testdatabasequeries::testNewOthersRecord()
{
    QVERIFY(m_dbmanager.get()->CreateNewRecord(m_othersContainer));
}

void Testdatabasequeries::testDatabaseState()
{
   QVERIFY(m_dbmanager.get()->CreateNewRecord(m_bookContainer));

    // Überprüfen, ob der neue Eintrag in der Datenbank vorhanden ist
   QVERIFY(databaseContainsEntry(m_bookContainer));
}

bool Testdatabasequeries::databaseContainsEntry(Datamanager::BOOK_CONTENT bookContainer)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery query(db);

        // Erstellen Sie die SQL-Abfrage, um zu überprüfen, ob das Buch vorhanden ist
        // ISBN sollte unique sein
        QString queryString = "SELECT COUNT(*) FROM books WHERE isbn = :isbn";
        query.prepare(queryString);
        query.bindValue(":isbn", bookContainer.isbn);

        if (query.exec()) {
            if (query.next()) {
                int count = query.value(0).toInt();
                return count > 0; // Wenn die Anzahl größer als 0 ist, ist das Buch vorhanden
            }
        } else {
            qDebug() << "Error executing query in databaseContainsEntry(): " << query.lastError().text();
        }
    } else {
        qDebug() << "Database connection is not open.";
    }

    return false; // Rückgabe, falls ein Fehler auftritt
}

