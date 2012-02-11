#-------------------------------------------------
#
# Project created by QtCreator 2011-01-05T21:58:53
#
#-------------------------------------------------

QT       += core xml

#QT       -= gui

TARGET = plotsauce
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
src/survex/img.c \
src/survex/filename.c \
src/survex/message.c \
src/survex/osdepend.c \
src/survex/useful.c \
src/survex/cmdline.c \
    src/psStation.cpp \
    src/psLine.cpp \
    src/psSurvex3DParser.cpp \
src/psStationLookup.cpp \
    src/psXMLWriter.cpp

HEADERS += src/survex/img.h \
src/survex/useful.h \
src/survex/config.h \
src/survex/debug.h \
src/survex/filelist.h \
src/survex/filename.h \
src/survex/img.h \
src/survex/message.h \
src/survex/osalloc.h \
src/survex/osdepend.h \
src/survex/ostypes.h \
src/survex/useful.h \
src/survex/whichos.h \
src/survex/cmdline.h \
    src/psStation.h \
    src/psLine.h \
    src/psSurvex3DParser.h \
src/psStationLookup.h \
    src/psXMLWriter.h

INCLUDEPATH += src \
src/survex

DEPENDPATH += src \
src/survex

DEFINES += IMG_API_VERSION=1 \
   IMG_HOSTED

macx:LIBS += -lz

OBJECTS_DIR = .obj
