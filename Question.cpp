#include "Question.hpp"

Question::Question()
{
    m_id = -1;
    m_questionText = "";
    m_answerText = "";
}


Question::Question(int id, QString questionText, QString answerText):
    m_id(id),
    m_questionText(questionText),
    m_answerText(answerText)
{
    // Nothing to do here
}


Question::Question(const Question& copyFrom)
{
    this->m_id = copyFrom.m_id;
    this->m_answerText = copyFrom.m_answerText;
    this->m_questionText = copyFrom.m_questionText;
}


Question& Question::operator=(const Question& rightSide)
{
    this->m_id = rightSide.m_id;
    this->m_answerText = rightSide.m_answerText;
    this->m_questionText = rightSide.m_questionText;

    return *this;
}


bool Question::operator==(const Question &rightSide)
{
    return ((m_id == rightSide.m_id) &&
            (m_questionText == rightSide.m_questionText) &&
            (m_answerText == rightSide.m_answerText));
}


bool Question::setQuestionText(QString text)
{
    // Assume failure until we are successful.
    bool ret = false;

    // Double check the values are valid
    //if ()
    //{
    // Now assign the value
    m_questionText = text;
    m_questionText.truncate(sMAX_QUESTION_TEXT_LENGTH);

    ret = true;
    //}

    return ret;
}


bool Question::setAnswerText(QString text)
{
    // Assume failure until we are successful.
    bool ret = false;

    // Double check the values are valid
    //if ()
    //{
    // Now assign the value
    m_answerText = text;
    m_answerText.truncate(sMAX_ANSWER_TEXT_LENGTH);

    ret = true;
    //}

    return ret;
}
