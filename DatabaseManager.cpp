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


QList<Category> DatabaseManager::readDatabase()
{
    QList<Category> categories;
    QList<Category>::iterator it;
    
    // Read the list of categories.
    // SELECT * FROM Category;
    
    // Loop through each category and grab all the questions.
    it = categories.begin();
    
    while (it != categories.end())
    {
        // Read list of questions that match this category.
        // SELECT * FROM Question WHERE catID = (it->getId());
    }
    
    return categories;
}


bool DatabaseManager::writeCategory(const Category& category)
{
    bool ret = false;   // Assume failure.
    QString commandStr;
    QString catName = sanitizeString(category.getName(), sMAX_CATEGORY_NAME_SIZE);
    sprintf(commandStr, "INSERT INTO Category ( id , name) VALUES ( %d , %s )", category.getId(), catName);
    
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
    QString questionString = sanitizeString(question.getQuestionText(), sMAX_QUESTION_TEXT_LENGTH);
    QString answerString = sanitizeString(question.getAnswerText(), sMAX_ANSWER_TEXT_LENGTH);
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
    return false;
}


bool DatabaseManager::disconnect()
{
    return false;
}


QString DatabaseManager::sanitizeString(QString str, int maxLength)
{
    QString ret = str;
    // Start by truncating the string
    if (ret.length() > maxLength)
    {
        ret = ret.substr(0, maxLength - 1);
    }
}
    
