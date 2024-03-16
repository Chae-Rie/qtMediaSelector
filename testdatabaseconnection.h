#ifndef TESTDATABASECONNECTION_H
#define TESTDATABASECONNECTION_H

#include <QObject>
#include <QTest>
#include <QSqlDatabase>

class TestDatabaseConnection : public QObject
{

private slots:
    void initTestCase();
    void testConnection();
    void testMyConnection();
    void cleanupTestCase();
};

#endif // TESTDATABASECONNECTION_H
