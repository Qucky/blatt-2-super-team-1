//============================================================================
// Name        : AlgDatII.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "word_table.h"
#include "words.h"


#include "mainwindow.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[]) {
    //Words w("  foo  123! - > @  @@bar\n   baz\n");
    //for(Words::Iterator it = w.begin(); it != w.end(); ++it) {
    //    cout << *it << endl;
    //}

    QApplication qApplication(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    return qApplication.exec();
}
