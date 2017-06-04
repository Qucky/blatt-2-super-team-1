#-------------------------------------------------
#
# Project created by QtCreator 2017-05-19T17:38:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlgDat_II
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    words.cpp \
    word_table.cpp

HEADERS  += mainwindow.h \
    words.h \
    word_table.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
