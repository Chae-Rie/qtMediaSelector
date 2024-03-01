#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QtSql/QSqlQueryModel> // Für die Abfrage von Inhalten aus der DB

class DbManager
{
public:
    DbManager();
    virtual ~DbManager();

 // Methoden
private:
    bool Connect(const std::string& connectionstring);
    bool Disconnect();

// Attribute
private:
    QSqlDatabase m_database;



};

#endif // DBMANAGER_H
