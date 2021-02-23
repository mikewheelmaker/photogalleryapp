QT += testlib quick
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../

SOURCES += tst_galleryproxymodelunittest.cpp \
            ../../galleryproxymodel.cpp
            ../../gallerymodel.cpp

HEADERS += ../../galleryproxymodel.h \
            ../../gallerymodel.h
            ../../utilities.h
