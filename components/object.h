#ifndef OBJECT_H
#define OBJECT_H

#include "bib/Vetor3D.h"
#include <iostream>

using namespace std;

class Object
{
    public:


    Vetor3D position, rotation, scale;
    bool active;
    Object *child, *parent;
    string serialize();
    Object deserialize(string str);

    Object();
};

#endif // OBJECT_H
