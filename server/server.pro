QT += core network
TEMPLATE = app
CONFIG += console c++11
CONFIG -= x86_64


SOURCES += src/main.cpp \
    src/connectionthread.cpp \
    src/server.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    src/connectionthread.h \
    src/server.h

