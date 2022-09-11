TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QT   += core gui opengl
LIBS += -lopengl32 -lfreeglut -lglu32
SOURCES += \
        entradas.cpp \
        entradas.cpp \
        iniciar_jogo.cpp \
        iniciar_jogo.cpp \
        leitura.cpp \
        leitura.cpp \
        main.cpp \
        textura.cpp \
        textura.cpp

HEADERS += \
    ../trabalhoFinal/pecas.h \
    objeto.h \
    objeto.h \
    pecas.h \
    pecas.h \
    tabuleiro.h \
    tabuleiro.h
