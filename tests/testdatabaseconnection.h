#ifndef TESTDATABASECONNECTION_H
#define TESTDATABASECONNECTION_H

#include <QObject>
#include <QTest>
#include <QSqlDatabase>


class TestDatabaseConnection : public QObject
{
    // Ohne das Macro findet er die Testfunktion nicht
    Q_OBJECT
private slots:
    void initTestCase();
    void testConnection();

    void cleanupTestCase();

private:

};

#endif // TESTDATABASECONNECTION_H
