#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T15:40:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MessageConverter
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp\
        fetsprocess.cpp\
        fsteprocess.cpp

HEADERS  += widget.h\
        fetsprocess.h\
        fsteprocess.h

FORMS    += widget.ui

QT += axcontainer
