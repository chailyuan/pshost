#-------------------------------------------------
#
# Project created by QtCreator 2017-12-07T18:52:35
#
#-------------------------------------------------
include($$PWD/../Base.pri)

QT += core gui network concurrent sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PasswordHost
TEMPLATE = app

CONFIG += c++11

include( $$PWD/../JQLibrary/JQLibrary.pri )

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS += -L$$DESTDIR \
        -lDbManager

INCLUDEPATH += $$PWD/../DbManager

DEPENDPATH += $$PWD/../DbManager
