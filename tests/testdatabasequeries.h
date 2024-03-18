#ifndef TESTDATABASEQUERIES_H
#define TESTDATABASEQUERIES_H

#include <QObject>
#include <QTest>
#include "../dbmanager.h"
#include "../datamanager.h"

class Testdatabasequeries : public QObject
{
    Q_OBJECT

// Alles innerhalb der slots-Reihe wird von dem Testframework ausgeführt
private slots:

    void initTestCase();
    void initTestCase_data();
    void cleanupTestCase();


    // -------
    void testTableCreation();
    void testNewBookRecord();
    void testNewMagazineRecord();
    void testNewOthersRecord();
    void testDatabaseState();

private:
    std::unique_ptr<DbManager> m_dbmanager;
    std::unique_ptr<Datamanager> m_datamanager;

    Datamanager::BOOK_CONTENT m_bookContainer;
    Datamanager::MAGAZINE_CONTENT m_magazineContainer;
    Datamanager::OTHERS_CONTENT m_othersContainer;


    bool databaseContainsEntry( Datamanager::BOOK_CONTENT bookContainer);
};

#endif // TESTDATABASEQUERIES_H
