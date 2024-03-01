#include "dbmanager.h"

DbManager::DbManager() {}

DbManager::~DbManager(){}


// Should connect client to local sqlite-database
bool DbManager::Connect(const std::string &connectionstring)
{
    //m_database.open();
    return false;
}

// Should disconnect client from local sqlite-database
bool DbManager::Disconnect()
{
    return false;
}
