#-------------------------------------------------
#
# Project created by QtCreator 2017-10-31T09:47:42
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RtvViewer
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


SOURCES += \
        main.cpp \
        MainWindow.cpp \
    RtvView.cpp \
    RtvScene.cpp \
    RtvContext.cpp \
    image_buffer/ImageBuffer.cpp \
    image_buffer/RtvImageLoader.cpp

HEADERS += \
        MainWindow.h \
    RtvView.h \
    RtvScene.h \
    RtvContext.h \
    image_buffer/ImageBuffer.h \
    image_buffer/ImageLoaderBase.h \
    image_buffer/RtvImageLoader.h

FORMS += \
        MainWindow.ui

RESOURCES += \
    resource.qrc
