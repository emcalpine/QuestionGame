#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include "Category.h"
#include "Question.hpp"
#include <QSqlDatabase>
#include <QSqlError>


// TODO: Make this a singleton class.
// TODO: Make this class its own thread to avoid blocking.
// TODO: Add support for multiple types of databases, in case users don't want to use MariaDB.
class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);

    // Destructor
    ~DatabaseManager();

    // This operation starts up the Database Manager
    bool initialize(QString databaseAddress,
                    QString username,
                    QString password);

    // This operation reads everything from the database
    QList<Category> readDatabase();

    // This operation writes a category to the database
    bool writeCategory(const Category& category);

    // This operation erases a category and all related questions in the database. Use with caution
    bool eraseCategory(const Category& category);

    // This operation writes a question to the database, linked to a category.
    bool writeQuestion(const Question& question,
                       const Category& category);

    // This operation erases a question from the database.
    bool eraseQuestion(const Question& question);

    // This operation renames a category in the database or adds it if the ID could not be found.
    bool renameCategory(const Category& category);

    // This operation edits a question in the database, or adds it if the ID could not be found.
    bool editQuestion(const Question& question);

    // This operation returns the last error.
    QString getLastError();


private:
    // This operation connects to the database
    bool connect();

    // This opertaion disconnects from the database
    void disconnect();

    // This operation ensures a string is safe to pass into an SQL statement.
    // Returns the sanitized string.
    QString sanitizeString(
            // The String to sanitize.
            const QString& str,
            // The maximum length for this string
            int maxLength);

    // This object is a handle to database
    QSqlDatabase m_db;


signals:

};


inline QString DatabaseManager::getLastError()
{
    return m_db.lastError().text();
}

#endif // DATABASEMANAGER_H
