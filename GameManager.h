#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "Category.h"
#include "DatabaseManager.h"
#include "Question.hpp"


// This class facilitates the game by keeping track of the categories and questions.
// This is also responsible for communicating between the UI and Database.
class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);

    // This operation starts up the game manager and configures everything necessary to begin operation.
    void initialize();

    // DATA MANAGEMENT
    // This operation adds a category to the list with a certain name. Duplicates will be ignored.
    void addCategory(QString name);

    // This operation removes a category of a particular name. All related questions will be removed as well.
    void removeCategory(QString name);

    // This operation adds a question to a particular category.
    void addQuestion(QString categoryName, QString questionText, QString answerText);

    // This operation removes a question.
    // Optionally, a category name can be provided to reduce the search time.
    void removeQuestion(QString questionText, QString answerText, QString categoryName = "");

    // This operation returns a list of questions for a category. Used to populate the table.
    QList<Question> getQuestionList(QString categoryName);

    // GAME MANAGEMENT
    // This operation returns the names of 3 Categories, each with at least one eligible question.
    QList<QString> get3EligibleCategories();

    // This operation selects a pseudo-random question from a particular category.
    Question getRandomQuestion(QString categoryName);

    // This operation resets all the asked questions.
    void reset();

    // This operation returns a list of all the categories, used upon initialization.
    QList<Category> getAllCategories();

    // TEMPORARY
    bool isDbConnected();

    QString getDbError();


private:    
    // A list of the categories in the game.
    QList<Category> m_categories;

    // For now, an instance of the DatabaseManager. TODO: make the DM static.
    DatabaseManager dm;

    // This operation returns an iterator pointing to the Category of a given name.
    QList<Category>::iterator findCategory(QString name);

    // This operation returns a question object matching a String.
    Question findQuestion(QString questionText, QString categoryName = "");

    // A flag indicating the DB Connected. TEMPORARY.
    bool m_dbConnected;

signals:

};

inline bool GameManager::isDbConnected()
{
    return m_dbConnected;
}

inline QString GameManager::getDbError()
{
    return dm.getLastError();
}

#endif // GAMEMANAGER_H
