#include "testdatabaseconnection.h"



void TestDatabaseConnection::initTestCase()
{
// ":memory:" gibt der Funktion an, dass die DB im Ram gespeichert wird und zum Ende
// der Laufzeit auch wieder gelöscht wird
    // Set up database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:"); // In-memory database for testing
    QVERIFY(db.open());
}

void TestDatabaseConnection::testConnection()
{
    QSqlDatabase db = QSqlDatabase::database();
    QVERIFY(db.isValid());
    QVERIFY(db.isOpen());
}

void TestDatabaseConnection::cleanupTestCase()
{
    // Close database connection
    QSqlDatabase::database().close();
}


