TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGL -lglut -lGLU
HEADERS += camera.h common_header.h
SOURCES += main.cpp camera.cpp


