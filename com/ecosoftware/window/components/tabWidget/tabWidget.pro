#-------------------------------------------------
#
# Project created by QtCreator 2018-04-24T14:22:33
#
#-------------------------------------------------

QT       -= gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core

TARGET = TabWidget
TEMPLATE = lib

DEFINES += TABWIDGET_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
  TabWidget.cpp \
  ShowHideTabAct.cpp \
    CornerWidget.cpp \
    TabBar.cpp

HEADERS += \
  TabWidget_global.h \
  TabWidget.h \
  ShowHideTabAct.h \
    CornerWidget.h \
    TabBar.h

DESTDIR = ../

UI_DIR = ../../../../../ui
MOC_DIR = ../../../../../moc
OBJECTS_DIR = ../../../../../obj
RCC_DIR = ../../../../../rcc

win32:CONFIG(release, debug|release): LIBS += \
  -L$$OUT_PWD/../ -lactions
else:win32:CONFIG(debug, debug|release): LIBS += \
  -L$$OUT_PWD/../ -lactions
else:unix: LIBS += \
  -L$$OUT_PWD/../ -lactions

INCLUDEPATH += \
  $$PWD/../actions

DEPENDPATH += \
  $$PWD/../actions

unix {
  target.path = /usr/lib
  INSTALLS += target
}
