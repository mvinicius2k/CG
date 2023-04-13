#pragma once
#include <iostream>
#include <vector>
#include "../bib/Vetor3D.h"
#include <utils/serializable.h>
using namespace std;


// Contém comportamentos padrão para todo objeto do mundo, como translação, rotação, seleção etc
class Object : Serializable<Object>
{
private:
    

protected:
    
    // Comportamento do objeto pelo movimento do mouse
    void mouseInput();
    // Desenha o objeto chamando as funções de desenhar do opengl
    virtual void draw();
    bool _selected;
    bool _selectedByParent; //se está selecionado pela hierarquia (se a casa é selecionada, as paredes, chão etc são selecionadas tambem)



public:
    bool _disableShadow;
    bool _disableTranslate, _disableRotation, _disableScale;
    inline static float TranslateSensibility = 1.f;
    inline static float RotataSensibility = 10.f;
    inline static float ScaleSensibility = 1.f;
    inline static bool ShowInfos = false;
    string _name;
    Vetor3D _position, _rotation, _scale;
    bool _active;
    float _originSize = 1.f;
    vector<Object*> _children; //objetos filhos. Os objetos filhos são posicionados/rotacionados/escalados localmente em relação ao pai
    bool isSelected();
    virtual void setSelected(bool value, bool selectedByParent = false);

    void syncGUI();
    //Foi feito para englobar o draw(). É responsável por aplicar as transformações no objeto a cada frame. 
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


