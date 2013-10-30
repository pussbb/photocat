#-------------------------------------------------
#
# Project created by QtCreator 2012-07-24T11:16:06
#
#-------------------------------------------------

QT       += core gui

TARGET = photocat
TEMPLATE = app

unix{
    OBJECTS_DIR = ./obj/
    MOC_DIR = ./obj/
    DESTDIR = ../bin/
    UI_DIR = ./obj/
}

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
