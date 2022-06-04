#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include "../bib/Vetor3D.h"
using namespace std;



class Object
{
protected:
    

    void mouseInput();
    virtual void draw() = 0;
    bool _selected;



    public:


    Vetor3D _position, _rotation, _scale;
    bool _active, _drawOrigin, _showName, _showInfos;
    float _drawOriginSize;
    vector<Object*> _childs;
    bool isSelected();
    void setSelected(bool value);

    virtual string serialize();
    //virtual T& deserialize<T>(string str) = 0;
    void render();


    void renderInfos();
    
    

    Object();
    ~Object();
};

#endif // OBJECT_H
