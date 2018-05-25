#-------------------------------------------------
#
# Project created by QtCreator 2018-03-20T09:29:34
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = appcollapsedTabs
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS = \
  MainWindow.h

SOURCES = \
  main.cpp \
  MainWindow.cpp

DESTDIR = ../

win32:CONFIG(release, debug|release): LIBS += \
  -L$$OUT_PWD/../../com/ecosoftware/window/components/ -lactions \
  -L$$OUT_PWD/../../com/ecosoftware/window/components/ -lTabWidget
else:win32:CONFIG(debug, debug|release): LIBS += \
  -L$$OUT_PWD/../../com/ecosoftware/window/components/ -lactions \
  -L$$OUT_PWD/../../com/ecosoftware/window/components/ -lTabWidget
else:unix: LIBS += \
  -L$$OUT_PWD/../../com/ecosoftware/window/components/ -lactions \
  -L$$OUT_PWD/../../com/ecosoftware/window/components/ -lTabWidget

INCLUDEPATH += \
  $$PWD/../../com/ecosoftware/window/components/actions \
  $$PWD/../../com/ecosoftware/window/components/tabWidget

DEPENDPATH += \
  $$PWD/../../com/ecosoftware/window/components/actions \
  $$PWD/../../com/ecosoftware/window/components/tabWidget
