#-------------------------------------------------
#
# Project created by QtCreator 2014-04-09T14:21:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SWP2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qgraphicsitemprototype.cpp \
    qgraphicsitemfactory.cpp \
    qgraphicsitemcomposite.cpp \
    graphicsscene.cpp \
    buttonwidgetmediator.cpp \
    commands.cpp

HEADERS  += mainwindow.h \
    qgraphicsitemprototype.h \
    qgraphicsitemfactory.h \
    qgraphicsitemcomposite.h \
    qexception.h \
    graphicsscene.h \
    buttonwidgetmediator.h \
    commands.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
