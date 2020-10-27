#-------------------------------------------------
#
# Project created by QtCreator 2019-06-17T09:02:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = waylandsink
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        GstWidget.cpp \
        main.cpp

HEADERS += \
    GstWidget.h


unix {
   CONFIG += link_pkgconfig
   PKGCONFIG += gstreamer-1.0 gstreamer-audio-1.0 gstreamer-video-1.0 televictouring
   INSTALLS += target
}

x11 {
    LIBS += -lX11
}
