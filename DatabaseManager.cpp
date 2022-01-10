#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{

}


DatabaseManager::~DatabaseManager()
{
    //disconnect();
}


bool DatabaseManager::initialize(QString databaseAddress, QString username, QString password)
{
    // TODO

    //connect();
    return true;
}
