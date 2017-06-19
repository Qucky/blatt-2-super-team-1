#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "words.h"

#include <map>

#include <QFileDialog>

namespace Ui {

class MainWindow;

}
/**
 * Diese Klasse repräsentiert unsere GUI.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /**
     * Diese Methode wird aufgerufen, sobald ein neuer Suchauftrag gestartet wurde.
     */		
    void on_searchButton_clicked();
    /**
     * Diese Methode verändert die GUI, sodass eine Datei bzw. ein Text eingelesen werden kann.
     * Dabei wird entweder ein Filebrowser oder ein Textfeld angezeigt.
     */
    void on_switchReadModeButton_clicked();

    /**
     * Diese Methode liest eine Datei bzw einen Text ein und speichert den Inhalt zur weiteren
     * Bearbeitung ab.
     */
    void on_readButton_clicked();

private:
    Ui::MainWindow *ui;
    Words* word;
    bool readText = true;
};

#endif // MAINWINDOW_H
