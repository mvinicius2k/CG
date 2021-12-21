TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += bib
INCLUDEPATH += gui_glut

LIBS += -lGL -lGLU -lglut -l3ds -lSDL_image

SOURCES += main.cpp \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/model3ds.cpp \
    bib/Vetor3D.cpp \
    gui_glut/extra.cpp \
    gui_glut/gui.cpp \
    trab1/Objeto.cpp \
    trab1/Plano.cpp \
    trab1/Cubo.cpp \
    trab1/Casa.cpp

HEADERS += \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/model3ds.h \
    bib/Vetor3D.h \
    gui_glut/extra.h \
    gui_glut/gui.h \
    trab1/Objeto.h \
    trab1/Cubo.h \
    trab1/Plano.h \
    trab1/Cubo.h \
    trab1/Casa.h
