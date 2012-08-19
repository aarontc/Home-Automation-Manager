#-------------------------------------------------
#
# Project created by QtCreator 2011-03-08T17:24:09
#
#-------------------------------------------------

QT       += core gui

TARGET = HomeAutomationManagerFrontend
TEMPLATE = app


SOURCES += main.cpp\
	mainwindow.cpp \
	receiver.cpp \
	HarmanKardonAVR645Receiver.cpp

HEADERS  += mainwindow.h \
	receiver.h \
	HarmanKardonAVR645Receiver.h

FORMS    += mainwindow.ui

LIBS	+= -lqextserialport -lxosd
