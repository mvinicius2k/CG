#pragma once
#include <iostream>
#include <vector>
#include "../bib/Vetor3D.h"
#include <utils/serializable.h>
using namespace std;



class Object : Serializable<Object>
{
private:
    

protected:
    

    void mouseInput();
    virtual void draw();
    bool _selected, _selectedByParent;

    bool _disableTranslate, _disableRotation, _disableScale;


    public:

    string _name;
    Vetor3D _position, _rotation, _scale;
    bool _active, _showName, _showInfos;
    float _originSize;
    vector<Object*> _children;
    bool isSelected();
    void setSelected(bool value, bool selectedByParent = false);

    void render();
    void consoleLog(string text);

    void renderInfos();
    
    

    Object(string name = "Novo Objeto");
    ~Object();

public:
   


    // Herdado por meio de Serializable
    virtual std::string serialize() override;

    virtual Object* deserialize(std::vector<std::string>::iterator& lines) override;

};


