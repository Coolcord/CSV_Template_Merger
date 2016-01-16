#-------------------------------------------------
#
# Project created by QtCreator 2016-01-14T10:34:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TemplateMerger
TEMPLATE = app


SOURCES += main.cpp\
        Main_Window.cpp \
    Merger.cpp \
    CSV_Helper.cpp \
    Merger_Thread.cpp

HEADERS  += Main_Window.h \
    Merger.h \
    CSV_Helper.h \
    Merger_Thread.h

FORMS    += Main_Window.ui
