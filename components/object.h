#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include "bib/Vetor3D.h"
using namespace std;

class Object
{
    public:


    Vetor3D _position, _rotation, _scale;
    bool _active, _selected, _drawOrigin, _showName;
    float _drawOriginSize;
    string _name;

    virtual string serialize() = 0;
    virtual Object& deserialize(string str) = 0;
    virtual void mouseInput();
    void draw();



    Object(string name = nullptr);
    ~Object();
};

#endif // OBJECT_H
