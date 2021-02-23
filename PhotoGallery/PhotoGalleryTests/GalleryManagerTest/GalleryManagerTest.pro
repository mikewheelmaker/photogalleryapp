QT += testlib sql network quick
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../

SOURCES += tst_gallerymanagerunittest.cpp \
            ../../gallerymanager.cpp \
            ../../gallerymodel.cpp \
            ../../galleryproxymodel.cpp \
            ../../databasemanager.cpp \
            ../../networkhandler.cpp

HEADERS += ../../gallerymanager.h \
            ../../gallerymodel.h \
            ../../galleryproxymodel.h \
            ../../databasemanager.h \
            ../../networkhandler.h \
            ../../utilities.h
