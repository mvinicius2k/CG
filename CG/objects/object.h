#pragma once
#include <iostream>
#include <vector>
#include "../bib/Vetor3D.h"
#include <utils/serializable.h>
using namespace std;


// Cont�m comportamentos padr�o para todo objeto do mundo, como transla��o, rota��o, sele��o etc
class Object : Serializable<Object>
{
private:
    

protected:
    
    // Comportamento do objeto pelo movimento do mouse
    void mouseInput();
    // Desenha o objeto chamando as fun��es de desenhar do opengl
    virtual void draw();
    bool _selected;
    bool _selectedByParent; //se est� selecionado pela hierarquia (se a casa � selecionada, as paredes, ch�o etc s�o selecionadas tambem)



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
    vector<Object*> _children; //objetos filhos. Os objetos filhos s�o posicionados/rotacionados/escalados localmente em rela��o ao pai
    bool isSelected();
    virtual void setSelected(bool value, bool selectedByParent = false);

    void syncGUI();
    //Foi feito para englobar o draw(). � respons�vel por aplicar as transforma��es no objeto a cada frame. 
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


