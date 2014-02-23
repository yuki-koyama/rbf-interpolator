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
    visualizingwidget.cpp \
    Interpolator/interpolator.cpp

HEADERS  += mainwindow.h \
    visualizingwidget.h \
    Interpolator/interpolator.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../include
