#-------------------------------------------------
#
# Project created by QtCreator 2013-06-03T14:46:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ANN_BP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ann_bp.cpp \
    neuron.cpp

HEADERS  += mainwindow.h \
    ann_bp.h \
    neuron.h

FORMS    += mainwindow.ui
