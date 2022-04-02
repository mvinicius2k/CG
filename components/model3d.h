#ifndef MODEL3D_H
#define MODEL3D_H
#include "object.h"
#include "bib/Vetor3D.h"
#include "utils/material.h"

using namespace std;

class Model3D{



public:
    Vetor3D *vertex;
    Material *materials;

    Model3D();
};

#endif // MODEL3D_H
