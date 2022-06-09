#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include "../bib/Vetor3D.h"
#include "../utils/serializable.h"
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
    bool _active, _drawOrigin, _showName, _showInfos;
    float _originSize;
    vector<Object*> _children;
    bool isSelected();
    void setSelected(bool value, bool selectedByParent = false);

    template<typename  T>
    T* deserialize(string str);
    void render();
    void consoleLog(string text);

    void renderInfos();
    
    

    Object(string name = "Novo Objeto");
    ~Object();

    // Herdado por meio de Serializable
    virtual Object* deserialize(std::string& str);
    virtual string serialize();
};

#endif // OBJECT_H
