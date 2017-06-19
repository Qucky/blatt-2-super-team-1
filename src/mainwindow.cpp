#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "word_table.h"
#include "words.h"


#include <iostream>


// Resize einbauen
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->fileEdit->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_searchButton_clicked()
{
    ui->positionInputLabel->setText("");
    std::string searchString = ui->searchEdit->text().toStdString();

    if(word != NULL && !searchString.empty()) {
        Words::entry_ptr entry_ptr = word->find(searchString);

        if(entry_ptr != NULL) {

            std::string positions = "";

            std::list<long> positionList = entry_ptr->positions();
            for(std::list<long>::iterator it = positionList.begin();
                it != positionList.end();
                it++) {
                positions += std::to_string(*it);
                positions += ' ';
                //positions.append(std::to_string(*it));
            }
            ui->positionInputLabel->setText(QString::fromStdString(positions));
        }
    }
}

void MainWindow::on_switchReadModeButton_clicked()
{
    if(readText) {
        readText = false;
        ui->switchReadModeButton->setText("Text");
        ui->readButton->setText("Read file");
        ui->textEdit->hide();
        ui->fileEdit->show();
    } else {
        readText = true;
        ui->switchReadModeButton->setText("File");
        ui->readButton->setText("Read text");
        ui->fileEdit->hide();
        ui->textEdit->show();
    }
}

void MainWindow::on_readButton_clicked()
{
    if(readText) {
        QString qText = ui->textEdit->toPlainText();
        std::string text = qText.toLocal8Bit().constData();

        if(text != "") {
            word = new Words(text);
        }
    } else {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("Text Files (*.txt)"));
        if(fileName != "") {
            ui->fileEdit->setText(fileName);

            word = Words::newFromFile(fileName.toStdString());
        }
    }
}
