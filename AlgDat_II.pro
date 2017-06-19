#-------------------------------------------------
#
# Project created by QtCreator 2017-05-19T17:38:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlgDat_II
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/words.cpp \
    src/word_table.cpp \
    src/block.cpp

HEADERS  += include/mainwindow.h \
    include/words.h \
    include/word_table.h \
    include/block.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
