TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += /home/cexcell/opencv/release/lib/*.so

SOURCES += main.cpp

OTHER_FILES += \
    haarcascade_frontalface_default.xml

