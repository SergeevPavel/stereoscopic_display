TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGL -lglut -lGLU /usr/local/lib/libopencv*
HEADERS += camera.h controller.h common_header.h
SOURCES += main.cpp camera.cpp controller.cpp

