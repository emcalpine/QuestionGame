#include "GameManager.h"

GameManager::GameManager(QObject *parent) :
    QObject(parent),
    dm()
{
    dm.initialize("localhost", "root", "root");
}

void GameManager::addCategory(QString name)
{
    // Find the next ID
    int id = 0;
    QList<Category>::iterator it;
    bool unique = false;
    while(unique == false)
    {
        unique = true;
        id++;
        it = m_categories.begin();
        while (it != m_categories.end())
        {
            if (it->getId() == id)
            {
                unique = false;
            }
            it++;
        }

    }

    Category cat = Category(id, name);

    // Add it to the list
    m_categories.push_back(cat);

    // Update the Database
    //dm.writeCategory(cat);
}


void GameManager::removeCategory(QString name)
{
    QList<Category>::iterator it = findCategory(name);

    //dm.eraseCategory(*it);

    m_categories.erase(it);
}


void GameManager::addQuestion(QString categoryName, QString questionText, QString answerText)
{
    // Find the next available question ID.
    // Naive approach for now TODO: improve search
    int id = 0;
    QList<Category>::iterator it;
    QList<Question> qList;
    QList<Question>::iterator qIt;
    bool unique = false;
    while(unique == false)
    {
        unique = true;
        id++;
        it = m_categories.begin();
        while (it != m_categories.end())
        {
            qList = it->getAllQuestions();
            qIt = qList.begin();
            while (qIt != qList.end())
            {
                if (qIt->getId() == id)
                {
                    unique = false;
                    break;
                }
                qIt++;
            }

            // Cut down on execution time by shorting out if we found a match.
            if (unique == false)
            {
                break;
            }
            it++;
        }
    }

    // Create the Question
    Question question = Question(id, questionText, answerText);

    // Insert the Question into the Category
    it = findCategory(categoryName);
    it->addQuestion(question);

    // Inform the database.
    //dm.writeQuestion(question, *it);
}


void GameManager::removeQuestion(QString questionText, QString answerText, QString categoryName)
{
    // Find the Category
    QList<Category>::iterator it = findCategory(categoryName);

    if (it != m_categories.end())
    {
        Question question = it->findQuestion(questionText);
        // Instruct it to remove the question.
        it->removeQuestion(question);

        // Inform the database.
        //dm.eraseQuestion(question);
    }

}


QList<Question> GameManager::getQuestionList(QString categoryName)
{
    QList<Category>::iterator it = findCategory(categoryName);

    if (it != m_categories.end())
    {
        return it->getAllQuestions();
    }
    else
    {
        return QList<Question>();
    }
}


QList<QString> GameManager::get3EligibleCategories()
{
    QList<QString> list;
    int retries = 0;
    // TODO: no magic number
    for (int i = 0; i < 3; i++)
    {
        int randomIndex = abs(rand()) % m_categories.size();
        if (m_categories.at(randomIndex).getNumEligibleQuestions() > 0)
        {
            bool unique = true;
            QList<QString>::iterator it = list.begin();
            while (it != list.end())
            {
                if (*it == m_categories.at(randomIndex).getName())
                {
                    unique = false;
                }
                it++;
            }
            if (unique)
            {
                list.push_back(m_categories.at(randomIndex).getName());
            }
            else
            {
                // Was not a unique category. Try again.
                i--;
                retries++;
            }
        }
        else
        {
            // Category did not have any eligible questions.
            i--;
            retries++;
        }

        if (retries > 10)
        {
            break;
        }
    }

    return list;
}


Question GameManager::getRandomQuestion(QString categoryName)
{
    return findCategory(categoryName)->getNextQuestion();
}


void GameManager::reset()
{
    QList<Category>::iterator it = m_categories.begin();

    while (it != m_categories.end())
    {
        it->resetUsed();
        it++;
    }
}



// Private functions
QList<Category>::iterator GameManager::findCategory(QString name)
{
    QList<Category>::iterator it = m_categories.begin();

    while (it != m_categories.end())
    {
        if (it->getName() == name)
        {
            break;
        }
        it++;
    }

    return it;
}
