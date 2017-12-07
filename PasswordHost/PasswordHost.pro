#-------------------------------------------------
#
# Project created by QtCreator 2017-12-07T18:52:35
#
#-------------------------------------------------

QT += core gui network concurrent sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PasswordHost
TEMPLATE = app

CONFIG += c++11

include( $$PWD/../JQLibrary/JQLibrary.pri )

SOURCES += main.cpp\
        mainwindow.cpp \
    thread.cpp

HEADERS  += mainwindow.h \
    thread.h

FORMS    += mainwindow.ui
