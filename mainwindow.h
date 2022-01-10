#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include <QMainWindow>
#include "GameManager.h"
#include "Question.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AddCategoryButton_clicked();

    void on_RemoveCategoryButton_clicked();

    void on_AddQuestionButton_clicked();

    void on_RemoveQuestionButton_clicked();

    void on_CategoryListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_CategoryButton1_clicked();

    void on_CategoryButton2_clicked();

    void on_CategoryButton3_clicked();

    void on_NextButton_clicked();

    void on_ResetButton_clicked();

    void on_AnswerButton_clicked();

private:
    Ui::MainWindow *ui;

    GameManager gm;

    Question m_currentQuestion;

    void catButtonClicked(QString categoryName);
};
#endif // MAINWINDOW_H
