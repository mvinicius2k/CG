#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include "../bib/Vetor3D.h"
using namespace std;

//template <typename T>

class Object
{
protected:
    

    void mouseInput();
    virtual void draw() = 0;
    bool _selected;



    public:


    Vetor3D _position, _rotation, _scale;
    bool _active, _drawOrigin, _showName, _translate, _rotate, _escalete, _showInfos;
    float _drawOriginSize;

    bool isSelected();
    void setSelected(bool value);

    virtual string serialize();
    //virtual T& deserialize<T>(string str) = 0;
    void render();

    void offAllTransformActions();

    void renderInfos();
    
    

    Object();
    ~Object();
};

#endif // OBJECT_H
