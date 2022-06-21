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

    inline static float TranslateSensibility = 1.f;
    inline static float RotataSensibility = 10.f;
    inline static float ScaleSensibility = 1.f;
    inline static bool ShowInfos = false;
    string _name;
    Vetor3D _position, _rotation, _scale;
    bool _active;
    float _originSize = 1.f;
    vector<Object*> _children;
    bool isSelected();
    void setSelected(bool value, bool selectedByParent = false);

    void syncGUI();

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


