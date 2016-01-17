#-------------------------------------------------
#
# Project created by QtCreator 2016-01-14T10:34:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CSV_Template_Merger
TEMPLATE = app
CONFIG += c++11 pendantic Wall


SOURCES += main.cpp\
        Main_Window.cpp \
    Merger.cpp \
    CSV_Helper.cpp \
    Merger_Thread.cpp

HEADERS  += Main_Window.h \
    Merger.h \
    CSV_Helper.h \
    Merger_Thread.h \
    Error_Codes.h

FORMS    += Main_Window.ui

RC_FILE = CSV_Template_Merger.rc

DISTFILES +=
