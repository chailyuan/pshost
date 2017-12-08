#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T09:41:14
#
#-------------------------------------------------
include($$PWD/../Base.pri)

QT       += sql core

QT       -= gui

TARGET = DbManager
TEMPLATE = lib

DEFINES += DBMANAGER_LIBRARY

SOURCES += DbManager.cpp \
    ConfigInterface.cpp

HEADERS += DbManager.h\
        dbmanager_global.h \
    ConfigInterface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


