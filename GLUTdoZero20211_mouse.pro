TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += bib
INCLUDEPATH += gui_glut
INCLUDEPATH += trab1

LIBS += -lGL -lGLU -lglut -l3ds -lSDL_image

SOURCES += main.cpp \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/model3ds.cpp \
    bib/Vetor3D.cpp \
    components/home.cpp \
    components/model3d.cpp \
    components/object.cpp \
    gui_glut/extra.cpp \
    gui_glut/gui.cpp \
    utils/color.cpp \
    utils/material.cpp

HEADERS += \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/model3ds.h \
    bib/Vetor3D.h \
    components/home.h \
    components/model3d.h \
    components/object.h \
    gui_glut/extra.h \
    gui_glut/gui.h \
    utils/color.h \
    utils/material.h
