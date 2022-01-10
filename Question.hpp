#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <QObject>
#include <QString>

class Question : public QObject
{
    Q_OBJECT
public:
    // The default length of the question text. Unsigned as extra insurance against negative length arrays.
    static const unsigned int sMAX_QUESTION_TEXT_LENGTH = 512;

    // The default length of the answer text.
    static const unsigned int sMAX_ANSWER_TEXT_LENGTH = 128;

    // Default Constructor
    Question();

    // Copy Constructor
    Question(const Question& copyFrom);

    // Argumented Constructor
    Question(int id,
             QString questionText,
             QString answerText);

    // Assignment operator overload
    Question& operator=(const Question& rightSide);
    bool operator==(const Question& rightSide);

    // This operation returns the ID of the Question
    int getId() const;

    // This operation sets the Question text.
    bool setQuestionText(QString text);

    // This operation returns the Question text.
    QString getQuestionText() const;

    // This operation sets the Answer text.
    bool setAnswerText(QString text);

    // This operation returns the Answer text.
    QString getAnswerText() const;


private:
    // The ID of the question. This is also used as the key in the database.
    int m_id;

    // The text that makes up the question, leaving room for the null terminator.
    QString m_questionText;

    // The text that makes up the answer, leaving room for the null terminator.
    QString m_answerText;
};


inline int Question::getId() const
{
    return m_id;
}


inline QString Question::getQuestionText() const
{
    return m_questionText;
}


inline QString Question::getAnswerText() const
{
    return m_answerText;
}

#endif // QUESTION_HPP
