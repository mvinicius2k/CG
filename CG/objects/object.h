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
    bool _active, _drawOrigin, _showName, _showInfos;
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
    /*static Object* deserialize(std::string& str)
    {
        stringstream ss;
        string line;

        int state = 0;
        auto newObj = Object();

        stringstream ss(str);
        vector<string> result;

        while (ss.good())
        {
            string substr;
            getline(ss, substr, '\n');
            result.push_back(substr);
        }

        int cont = 0;
        for (auto & line : result)
        {
            if (Serialization::LineIsObject(line, typeid(Object).name()))
                state = 1;

            if (state == 1)
            {
                if (Serialization::TryAssing(line, NAMEOF(_active), &newObj._active))
                    continue;
                if (Serialization::TryAssing(line, NAMEOF(_disableRotation), &newObj._disableRotation))
                    continue;
                if (Serialization::TryAssing(line, NAMEOF(_disableScale), &newObj._disableScale))
                    continue;
                if (Serialization::TryAssing(line, NAMEOF(_disableTranslate), &newObj._disableTranslate))
                    continue;
                if (Serialization::TryAssing(line, NAMEOF(_position), &newObj._position))
                    continue;
                if (Serialization::TryAssing(line, NAMEOF(_rotation), &newObj._rotation))
                    continue;
                if (Serialization::TryAssing(line, NAMEOF(_sacle), &newObj._scale))
                    continue;
                if (Serialization::TryAssing(line, NAMEOF(_name), &newObj._name))
                    continue;
                
                string* output;
                if (Serialization::TryGetValue(line, NAMEOF(_children), output))
                {
                    
                    state = 2;
                }


            }

            if (state == 2)
            {
                auto it = result.begin() + cont;
                auto child = Model3D::Deserialize(it);
            }

            cont++;
        }


        return nullptr;
    }


    */


    // Herdado por meio de Serializable
    virtual std::string serialize() override;

    virtual Object* deserialize(std::vector<std::string>::iterator& lines) override;

};


