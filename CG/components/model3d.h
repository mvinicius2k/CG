#ifndef MODEL3D_H
#define MODEL3D_H
#include "object.h"
#include "../bib/Vetor3D.h"
#include "../utils/material.h"
#include <glut.h>

using namespace std;

class Model3D : Object{



public:
    Vetor3D *_lines;
    Material *_materials;
    GLenum _mode;

    Model3D& Home(
        float floorWidth = 7.f,
        float floorDepth = 10.f,
        float wallHeight = 2.8f,
        float peakRelativeHeight = .5f);
    Model3D& Table(
        float footerHeight = .7f,
        float feetSize = .1f,
        float feetMargin = .05f,
        float surfaceWidth = 1.f, 
        float surfaceDepth = 1.5f,
        float surfaceHeigth = .05f);
    

    Model3D(bool randomColors = true);
    ~Model3D();
};

#endif // MODEL3D_H
