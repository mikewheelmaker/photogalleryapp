QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../

SOURCES += tst_gallerymodelunittest.cpp \
            ../../gallerymodel.cpp

HEADERS += ../../gallerymodel.h \
            ../../utilities.h
