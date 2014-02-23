#-------------------------------------------------
#
# Project created by QtCreator 2014-02-21T21:22:11
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RBFInterpolator
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    interpolator.cpp \
    utility.cpp \
    visualizingwidget.cpp

HEADERS  += mainwindow.h \
    interpolator.h \
    utility.h \
    visualizingwidget.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../include
