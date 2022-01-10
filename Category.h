#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>
#include "Question.hpp"

class Category : public QObject
{
    Q_OBJECT
public:
    explicit Category(QObject *parent = nullptr);

    // Only provie an argumented constructor.
    Category(int id,
             QString name);
    // And a copy constructor
    Category(const Category& copyFrom);

    // Assignment operator overload
    Category& operator=(const Category& copyFrom);

    int getId() const;

    QString getName() const;

    // This operation returns a list of all its questions
    QList<Question> getAllQuestions() const;

    // This operation returns a pseudo-randomly chosen question from its eligible list
    Question getNextQuestion();

    // This operation returns a count of the eligible questions.
    int getNumEligibleQuestions() const;

    // This operation returns all used questions to the eligible list
    void resetUsed();

    // This operation adds a question to the category. Initially, it will be placed in the eligible question list.
    void addQuestion(Question question);
    void addQuestion(int id, QString questionText, QString answerText);

    // This operation removes a question from the category.
    void removeQuestion(Question question);
    void removeQuestion(QString quesitonText);
    void removeQuestion(int id);

    // This operation returns a question that matches a particular text.
    Question findQuestion(QString questionText) const;

private:
    // The ID of the category. This is also used as the primary key in the database.
    int m_id;

    // The name of the category
    QString m_name;

    // A list of eligible Questions that belong in this category.
    QList<Question> m_eligibleQuestions;

    // A list of already-used Questions in this category.
    QList<Question> m_usedQuestions;

signals:

};

inline int Category::getId() const
{
    return m_id;
}

inline QString Category::getName() const
{
    return m_name;
}

inline int Category::getNumEligibleQuestions() const
{
    return m_eligibleQuestions.size();
}

#endif // CATEGORY_H
