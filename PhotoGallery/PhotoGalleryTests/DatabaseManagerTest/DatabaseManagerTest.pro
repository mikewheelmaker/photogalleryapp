QT += testlib
QT += sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../

SOURCES += tst_databasemanagerunittest.cpp \
            ../../databasemanager.cpp

HEADERS += ../../databasemanager.h \
            ../../utilities.h
