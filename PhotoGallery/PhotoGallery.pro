QT += quick
QT += sql
QT += network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        databasemanager.cpp \
        gallerymanager.cpp \
        gallerymodel.cpp \
        galleryproxymodel.cpp \
        main.cpp \
        networkhandler.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    databasemanager.h \
    gallerymanager.h \
    gallerymodel.h \
    galleryproxymodel.h \
    networkhandler.h \
    utilities.h

DISTFILES +=
