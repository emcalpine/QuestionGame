#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addcategorydialogue.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gm()
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AddCategoryButton_clicked()
{
    QString name = ui->CategoryEdit->text();

#ifdef EXTRA_LOGGING
    printf("Trying to add category by name :%s\n", name.toStdString().c_str());
#endif


    gm.addCategory(name);
    ui->CategoryListWidget->addItem(name);

}


void MainWindow::on_RemoveCategoryButton_clicked()
{
    QListWidgetItem* itemToRemove = ui->CategoryListWidget->currentItem();
    QString name = itemToRemove->text();

#ifdef EXTRA_LOGGING
    printf("Trying to remove category by name :%s\n", name.toStdString().c_str());
#endif

    gm.removeCategory(name);
    ui->CategoryListWidget->removeItemWidget(itemToRemove);
    delete itemToRemove;
}


void MainWindow::on_AddQuestionButton_clicked()
{
    if (ui->CategoryListWidget->selectedItems().size() != 1)
    {
        // Not 1 Category selected. To avoid confusion, simply ignore the request.
        return;
    }
    QString categoryName = ui->CategoryListWidget->currentItem()->text();
    QString questionText = ui->QuestionEdit->text();
    QString answerText = ui->AnswerEdit->text();

    gm.addQuestion(categoryName, questionText, answerText);

    // Add the question to the ui table.
    int rowIndex = ui->QuestionTableWidget->rowCount();
    ui->QuestionTableWidget->insertRow(rowIndex);
    ui->QuestionTableWidget->setItem(rowIndex, 0, (new QTableWidgetItem(questionText, 0)));
    ui->QuestionTableWidget->setItem(rowIndex, 1, (new QTableWidgetItem(answerText, 0)));
}


void MainWindow::on_RemoveQuestionButton_clicked()
{
    if (ui->CategoryListWidget->selectedItems().size() != 1)
    {
        // Ignore all requests unless one category is selected
        return;
    }

    // Gather the data.
    QString categoryName = ui->CategoryListWidget->currentItem()->text();
    int rowIndex = ui->QuestionTableWidget->currentRow();
    QTableWidgetItem* question = ui->QuestionTableWidget->item(rowIndex, 0);
    QTableWidgetItem* answer = ui->QuestionTableWidget->item(rowIndex, 1);

    QString questionText = question->text();
    QString answerText = answer->text();

    // Remove it from the game
    gm.removeQuestion(questionText, answerText, categoryName);

    // Update the UI
    ui->QuestionTableWidget->removeRow(rowIndex);
}


void MainWindow::on_CategoryListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString categoryName;
    QList<Question> list;
    QList<Question>::iterator it;
    int rowIndex = 0;

    // Find the new category
    if (ui->CategoryListWidget->selectedItems().size() != 1)
    {
        // If more or less than 1 item is selected, do nothing.
        return;
    }
    categoryName = ui->CategoryListWidget->currentItem()->text();

    // Acquire the list of questions from that category
    list = gm.getQuestionList(categoryName);

    // Clear the table first
    ui->QuestionTableWidget->clear();
    while (ui->QuestionTableWidget->rowCount() > 0)
    {
        ui->QuestionTableWidget->removeRow(0);
    }

    // Display each of them in the table.
    it = list.begin();

    while(it != list.end())
    {
        ui->QuestionTableWidget->insertRow(rowIndex);
        ui->QuestionTableWidget->setItem(rowIndex, 0, (new QTableWidgetItem(it->getQuestionText(), 0)));
        ui->QuestionTableWidget->setItem(rowIndex, 1, (new QTableWidgetItem(it->getAnswerText(), 0)));

        it++;
        rowIndex++;
    }
}


void MainWindow::on_CategoryButton1_clicked()
{
    catButtonClicked(ui->CategoryButton1->text());
}


void MainWindow::on_CategoryButton2_clicked()
{
    catButtonClicked(ui->CategoryButton2->text());
}


void MainWindow::on_CategoryButton3_clicked()
{
    catButtonClicked(ui->CategoryButton3->text());
}


void MainWindow::on_NextButton_clicked()
{
    // Clean Text fields.
    ui->QuestionField->setText("");
    ui->AnswerField->setText("");

    // Get 3 Categories.
    QList<QString> names = gm.get3EligibleCategories();

    // Populate Buttons + enable
    if (names.size() >= 3)
    {
        ui->CategoryButton1->setText(names.at(0));
        ui->CategoryButton2->setText(names.at(1));
        ui->CategoryButton3->setText(names.at(2));

        ui->CategoryButton1->setEnabled(true);
        ui->CategoryButton2->setEnabled(true);
        ui->CategoryButton3->setEnabled(true);
    }
    else
    {
        ui->CategoryButton1->setText("Error");
    }

}


void MainWindow::on_ResetButton_clicked()
{
    gm.reset();

    // Automatically Queue up the next question. Just makes usage easier and updates the UI so the user gets some feedback.
    on_NextButton_clicked();
}


void MainWindow::on_AnswerButton_clicked()
{
    ui->AnswerField->setText(m_currentQuestion.getAnswerText());
}


void MainWindow::catButtonClicked(QString categoryName)
{
    // Disable Category buttons
    ui->CategoryButton1->setEnabled(false);
    ui->CategoryButton2->setEnabled(false);
    ui->CategoryButton3->setEnabled(false);

    // Grab eligible question.
    m_currentQuestion = gm.getRandomQuestion(categoryName);

    // Populate Question Field.
    ui->QuestionField->setText(m_currentQuestion.getQuestionText());
}

