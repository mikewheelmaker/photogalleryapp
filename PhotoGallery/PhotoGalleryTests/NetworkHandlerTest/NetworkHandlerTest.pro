QT += testlib network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../

SOURCES += tst_networkhandlerunittest.cpp \
            ../../networkhandler.cpp

HEADERS += ../../networkhandler.h \
            ../../utilities.h
