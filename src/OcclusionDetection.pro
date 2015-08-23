#-------------------------------------------------
#
# Project created by QtCreator 2015-07-05T19:28:41
#
#-------------------------------------------------

QT       += gui widgets

TARGET = OcclusionDetection
CONFIG   += console c++11

TEMPLATE = app

SOURCES += main.cpp \
    abstractocclusiondetecter.cpp \
    basicocclusiondetecter.cpp \
    displayer.cpp \
    occlusions.cpp \
    opticalflowdetecter.cpp \
    bilinearfilter.cpp \
    superfilter.cpp \
    opencvbasedocclusiondetecter.cpp

DISTFILES +=

HEADERS += \
    abstractocclusiondetecter.h \
    basicocclusiondetecter.h \
    displayer.h \
    occlusions.h \
    opticalflow.h \
    opticalflowdetecter.h \
    myimage.h \
    bilinearfilter.h \
    superfilter.h \
    opencvbasedocclusiondetecter.h

FORMS += \
    displayer.ui

LIBS += -lopencv_calib3d -lopencv_imgproc -lopencv_core -lopencv_imgcodecs
