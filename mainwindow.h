#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "words.h"

#include <map>

#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_searchButton_clicked();

    void on_switchReadModeButton_clicked();

    void on_readButton_clicked();

private:
    Ui::MainWindow *ui;
    Words* word;
    bool readText = true;
};

#endif // MAINWINDOW_H
