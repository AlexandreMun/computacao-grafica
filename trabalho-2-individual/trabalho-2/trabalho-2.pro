TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        leitura.cpp \
        main.cpp \
        textura.cpp

QT   += core gui opengl
LIBS += -lopengl32 -lfreeglut -lglu32

HEADERS += \
    objeto.h \
    textura.h
