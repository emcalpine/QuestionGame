#include "Category.h"

Category::Category(QObject *parent) : QObject(parent)
{

}


Category::Category(int id, QString name):
    m_id(id),
    m_name(name)
{
    // Nothing to do here.
}


Category::Category(const Category& copyFrom):
    m_id(copyFrom.m_id),
    m_name(copyFrom.m_name)
{
    QList<Question>::const_iterator it = copyFrom.m_eligibleQuestions.begin();

    while (it != copyFrom.m_eligibleQuestions.end())
    {
        m_eligibleQuestions.push_back(*it);
        it++;
    }

    it = copyFrom.m_usedQuestions.begin();

    while (it != copyFrom.m_usedQuestions.end())
    {
        m_usedQuestions.push_back(*it);
        it++;
    }
}


Category& Category::operator=(const Category& copyFrom)
{
    this->m_id = copyFrom.m_id;
    this->m_name = copyFrom.m_name;

    QList<Question>::const_iterator it = copyFrom.m_eligibleQuestions.begin();

    while (it != copyFrom.m_eligibleQuestions.end())
    {
        this->m_eligibleQuestions.push_back(*it);
        it++;
    }

    it = copyFrom.m_usedQuestions.begin();

    while (it != copyFrom.m_usedQuestions.end())
    {
        this->m_usedQuestions.push_back(*it);
        it++;
    }

    return *this;
}


QList<Question> Category::getAllQuestions() const
{
    QList<Question> ret;

    QList<Question>::const_iterator it = m_eligibleQuestions.begin();

    while (it != m_eligibleQuestions.end())
    {
        ret.push_back(*it);
        it++;
    }

    it = m_usedQuestions.begin();

    while (it != m_usedQuestions.end())
    {
        ret.push_back(*it);
        it++;
    }

    return ret;
}


Question Category::getNextQuestion()
{
    Question ret;

    if (m_eligibleQuestions.size() > 0)
    {
        int randomIndex = rand() % m_eligibleQuestions.size();
        ret = m_eligibleQuestions.at(randomIndex);
        m_usedQuestions.push_back(ret);
        m_eligibleQuestions.removeAt(randomIndex);
    }
    else
    {
        ret = Question();
    }

    return ret;
}


void Category::resetUsed()
{
    Question q;
    while (m_usedQuestions.size() > 0)
    {
        q = m_usedQuestions.first();
        m_usedQuestions.pop_front();

        m_eligibleQuestions.push_back(q);
    }
}


void Category::addQuestion(Question question)
{
    m_eligibleQuestions.push_back(question);
}


void Category::removeQuestion(Question question)
{
    // First search the eligible questions.
    QList<Question>::iterator it = m_eligibleQuestions.begin();

    while (it != m_eligibleQuestions.end())
    {
        if (*it == question)
        {
            break;
        }
        it++;
    }

    // If we found the question, remove it and return.
    if (it != m_eligibleQuestions.end())
    {
        m_eligibleQuestions.erase(it);
        return;
    }


    // Now for the used questions.
    it = m_usedQuestions.begin();

    while (it != m_usedQuestions.end())
    {
        if (*it == question)
        {
            break;
        }
        it++;
    }

    if (it != m_usedQuestions.end())
    {
        m_usedQuestions.erase(it);
    }
}


Question Category::findQuestion(QString questionText) const
{
    QList<Question>::const_iterator it = m_eligibleQuestions.begin();

    while (it != m_eligibleQuestions.end())
    {
        if (it->getQuestionText() == questionText)
        {
            return *it;
        }
        it++;
    }

    it = m_usedQuestions.begin();

    while (it != m_usedQuestions.end())
    {
        if (it->getQuestionText() == questionText)
        {
            return *it;
        }
        it++;
    }

    // No matching question found, return null Question.
    return Question();
}
