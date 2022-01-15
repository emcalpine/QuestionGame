#include "DatabaseManager.h"
#include <QSqlDriver>
//#include <qsql.h>

#include <iostream>
#include <fstream>


DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{

}


DatabaseManager::~DatabaseManager()
{
    //disconnect();
}


bool DatabaseManager::initialize(QString databaseAddress, QString username, QString password)
{
    bool ret = false;

    //Due to time constraints, an actual database will be implemented later.
    /*MYSQLDriver driver = new MYSQLDriver();

    m_db = QSqlDatabase::addDatabase("QMYSQL");
    if (m_db.isValid())
    {
        m_db.setHostName(databaseAddress);
        m_db.setDatabaseName("3questiongamedb");
        m_db.setUserName(username);
        m_db.setPassword(password);

        // Connect is put in a seperate function in case I want to try some reconnect logic.
        ret = connect();
    }*/

    //#TEMPORARY #FILEDB
    ret = true;

    return ret;
}


QList<Category> DatabaseManager::readDatabase()
{
    QList<Category> categories;
    QList<Category>::iterator it;
    
    // Read the list of categories.
    // SELECT * FROM Category;

    // #TEMPORARY #FILEDB
    std::ifstream catFileStream;
    catFileStream.open("categories.txt");

    while((catFileStream.is_open()) &&
          (!catFileStream.eof()))
    {
        const int sMAX_CAT_SIZE = 33;
        char catLine[sMAX_CAT_SIZE];
        int id = 0;

        memset(catLine, '\0', sMAX_CAT_SIZE);

        catFileStream.getline(catLine, sMAX_CAT_SIZE, ',');
        id = std::atoi(catLine);
        memset(catLine, '\0', sMAX_CAT_SIZE);

        catFileStream.getline(catLine, sMAX_CAT_SIZE, '\n');
        Category cat = Category(id, QString(catLine));

        categories.push_back(cat);
    }
    // #TEMP #FILEDB End

    
    /*// Loop through each category and grab all the questions.
    it = categories.begin();
    
    while (it != categories.end())
    {
        // Read list of questions that match this category.
        // SELECT * FROM Question WHERE catID = (it->getId());
        it++;
    }*/

    // #TEMP #FILEDB begin
    std::ifstream questionFileStream;
    questionFileStream.open("questions.txt");

    while ((questionFileStream.is_open()) &&
           (!questionFileStream.eof()))
    {
        const int sMAX_QUEST_SIZE = 1024;
        char questLine[sMAX_QUEST_SIZE];
        int id = 0;
        int catId = 0;
        QString questionText;
        QString answerText;

        memset(questLine, '\0', sMAX_QUEST_SIZE);

        questionFileStream.getline(questLine, sMAX_QUEST_SIZE, ',');
        id = std::atoi(questLine);
        memset(questLine, '\0', sMAX_QUEST_SIZE);

        questionFileStream.getline(questLine, sMAX_QUEST_SIZE, ',');
        catId = std::atoi(questLine);
        memset(questLine, '\0', sMAX_QUEST_SIZE);

        questionFileStream.getline(questLine, sMAX_QUEST_SIZE, ',');
        questionText = QString(questLine);
        memset(questLine, '\0', sMAX_QUEST_SIZE);

        questionFileStream.getline(questLine, sMAX_QUEST_SIZE, '\n');
        answerText = QString(questLine);

        Question question = Question(id, questionText, answerText);

        QList<Category>::iterator it = categories.begin();

        while (it != categories.end())
        {
            if (it->getId() == catId)
            {
                it->addQuestion(question);
            }
            it++;
        }
    }

    // #TEMP #FILEDB end
    
    return categories;
}


bool DatabaseManager::writeCategory(const Category& category)
{
    bool ret = false;   // Assume failure.
    QString commandStr;
    QString catName = sanitizeString(category.getName(), Category::sMAX_CATEGORY_NAME_LENGTH);
    //sprintf(commandStr, "INSERT INTO Category ( id , name) VALUES ( %d , %s )", category.getId(), catName);
    
    // Execute Command.
    
    return ret;
}


bool DatabaseManager::eraseCategory(const Category& category)
{
    bool ret = false;   // Assume failure.
    
    // Remove the category.
    // DELETE FROM Category WHERE id = category.getId();
    
    // Now remove all questions in that category.
    // DELETE FROM Question WHERE catId = category.getId();
    
    return ret;
}


bool DatabaseManager::writeQuestion(const Question& question, const Category& category)
{
    bool ret = false;
    QString questionString = sanitizeString(question.getQuestionText(), Question::sMAX_QUESTION_TEXT_LENGTH);
    QString answerString = sanitizeString(question.getAnswerText(), Question::sMAX_ANSWER_TEXT_LENGTH);
    // INSERT INTO Question (id, catId, questionText, answerText) VALUES ( question.getId(), category.getId(), question.getQuestionText(), question.getAnswerText());
    
    return ret;
}


bool DatabaseManager::eraseQuestion(const Question& question)
{
    bool ret = false;
    
    // DELETE FROM Question WHERE id = question.getId();
    
    return ret;
}


bool DatabaseManager::renameCategory(const Category& category)
{
    bool ret = false;
    
    // UPDATE Category SET name = category.getName() WHERE id = category.getId();
    
    return ret;
}


bool DatabaseManager::editQuestion(const Question& question)
{
    bool ret = false;
    
    // UPDATE Question SET questionText = question.getQuestionText() WHERE id = question.getId();
    // UPDATE Question SET answerText = question.getAnswerText() WHERE id = question.getId();
    
    return ret;
}


bool DatabaseManager::connect()
{
    return m_db.open();
}


void DatabaseManager::disconnect()
{
    return m_db.close();
}


QString DatabaseManager::sanitizeString(const QString& str, int maxLength)
{
    QString ret = str;
    // Start by truncating the string
    if (ret.length() > maxLength)
    {
        ret.truncate(maxLength);
    }

    return ret;
}
    
