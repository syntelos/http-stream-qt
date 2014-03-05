TEMPLATE = lib
TARGET = NetworkHTTPStream
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += NetworkDeviceConnectionTCP.h \
           NetworkHTTPStreamChunk.h \
           NetworkHTTPStreamClient.h \
           NetworkHTTPStreamHeader.h \
           NetworkHTTPStreamIO.h \
           NetworkHTTPStreamRequest.h \
           NetworkHTTPStreamResponse.h
SOURCES += NetworkDeviceConnectionTCP.cpp \
           NetworkHTTPStreamChunk.cpp \
           NetworkHTTPStreamClient.cpp \
           NetworkHTTPStreamIO.cpp \
           NetworkHTTPStreamRequest.cpp \
           NetworkHTTPStreamResponse.cpp
