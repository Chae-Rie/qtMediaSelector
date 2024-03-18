#include <QTest>
#include "testdatabaseconnection.h"
#include "testdatabasequeries.h"

int main(int argc, char *argv[])
{
    // Testen der Datenbankverbindung, ganz fundamental
    TestDatabaseConnection testDbConnection;
    QTest::qExec(&testDbConnection, argc, argv);

    Testdatabasequeries testDbQueries;
    QTest::qExec(&testDbQueries, argc, argv);
}


