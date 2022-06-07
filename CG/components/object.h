#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include "../bib/Vetor3D.h"
using namespace std;



class Object
{
private:
    

protected:
    

    void mouseInput();
    virtual void draw() = 0;
    bool _selected, _selectedByParent;




    public:

    string _name;
    Vetor3D _position, _rotation, _scale;
    bool _active, _drawOrigin, _showName, _showInfos;
    float _drawOriginSize;
    vector<Object*> _children;
    bool isSelected();
    void setSelected(bool value, bool selectedByParent = false);

    virtual string serialize();
    //virtual T& deserialize<T>(string str) = 0;
    void render();
    void consoleLog(string text);

    void renderInfos();
    
    

    Object(string name = "Novo Objeto");
    ~Object();
};

#endif // OBJECT_H
