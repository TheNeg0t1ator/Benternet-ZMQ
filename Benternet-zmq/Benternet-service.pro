TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += ZMQ_STATIC
LIBS += -L$$PWD/../lib -lzmq -lws2_32 -lIphlpapi
INCLUDEPATH += $$PWD/../include

SOURCES += service.cpp \
    fileclass.cpp \
    inputOutput.cpp \
    zmq_service.cpp \
    cJSON.c

HEADERS += \
    fileclass.h \
    inputOutput.h \
    zmq_service.h \
    cJSON.h
