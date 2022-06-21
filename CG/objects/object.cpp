
#include "object.h"
#include <windows.h>
#include "../gui_glut/gui.h"
#include <string>
#include <sstream>
#include "../utils/serialization.h"
#include "../utils/strings.h"
#include <utils/mouse.h>
using namespace std;




Object::Object(string name)
{
    _name = name;
    _active = true;
    _scale = Vetor3D(1.f, 1.f, 1.f);
    
}

Object::~Object() {

}




void Object::draw()
{
}

void Object::render()
{
    if (!_active)
        return;
    if (_selected && !_selectedByParent)
        mouseInput();

    glPushMatrix();
    {
        
        
        

        glTranslatef(_position.x, _position.y, _position.z);
        glRotatef(_rotation.x, 1,0,0);
        glRotatef(_rotation.y, 0, 1, 0);
        glRotatef(_rotation.z, 0, 0, 1);
        if(_showInfos)
            GUI::drawOrigin(_originSize);
        glScalef(_scale.x, _scale.y, _scale.z);

        draw();
        if (_showInfos)
            renderInfos();

        if (_children.size() > 0)
            for (auto child : _children)
                child->render();

    } glPopMatrix();


}

void Object::consoleLog(string text)
{
    cout << _name << ": " << text << endl;

}


void Object::renderInfos()
{
    auto infoTxt = string("posição: ")
        .append(Strings::Vector3DToString(_position))
        .append(" rotação: ")
        .append(Strings::Vector3DToString(_rotation))
        .append(" escala: ")
        .append(Strings::Vector3DToString(_scale));

    Strings::DrawString(_position.x, _position.y, _position.z, infoTxt);
}

void Object::mouseInput()
{
    if (!_disableTranslate)
    {
        _position.x = Mouse::Step(glutGUI::tx);
        _position.y = Mouse::Step(glutGUI::ty);
        _position.z = Mouse::Step(glutGUI::tz);

    }

    if (!_disableRotation)
    {
        _rotation.x = Mouse::Step(glutGUI::ax);
        _rotation.y = Mouse::Step(glutGUI::ay);
        _rotation.z = Mouse::Step(glutGUI::az);

    }

    if (!_disableScale)
    {
        _scale.x = Mouse::Step(glutGUI::sx);
        _scale.y = Mouse::Step(glutGUI::sy);
        _scale.z = Mouse::Step(glutGUI::sz);

    }

}

bool Object::isSelected()
{
    return _selected;
}



void Object::setSelected(bool value, bool selectedByParent)
{

    _selectedByParent = selectedByParent;
    if (value && !_selectedByParent)
    {
        glutGUI::ax = _rotation.x;
        glutGUI::ay = _rotation.y;
        glutGUI::az = _rotation.z;

        glutGUI::sx = _scale.x;
        glutGUI::sy = _scale.y;
        glutGUI::sz = _scale.z;

        glutGUI::tx = _position.x;
        glutGUI::ty = _position.y;
        glutGUI::tz = _position.z;

    }

    _selected = value;
    for (auto child : _children)
        child->setSelected(value, true);
}


string Object::serialize() 
{
    stringstream childrenString;
    childrenString << "[" << endl;
    int i = 0;
    for (auto child : _children)
        childrenString << child->serialize();
    childrenString << "]";
    auto object = stringstream();
    object << typeid(Object).name() << endl
        << NAMEOF(_active) << "=" << to_string(_active) << endl
        << NAMEOF(_disableRotation) << "=" << to_string(_disableRotation) << endl
        << NAMEOF(_disableTranslate) << "=" << to_string(_disableTranslate) << endl
        << NAMEOF(_disableScale) << "=" << to_string(_disableScale) << endl
        << NAMEOF(_name) << "=" << _name << endl
        << NAMEOF(_position) << "=" << Strings::Vector3DToString(_position) << endl
        << NAMEOF(_rotation) << "=" << Strings::Vector3DToString(_rotation) << endl
        << NAMEOF(_scale) << "=" << Strings::Vector3DToString(_scale) << endl
        << NAMEOF(_children) << "=" << childrenString.str() << endl
        ;

    return object.str();
}

void qualquer(std::string& str)
{

}
Object* Object::deserialize(std::vector<std::string>::iterator& lines)
{
    
    if (Serialization::LineIsObject(*lines++, *this)) 
    {
        _active = Serialization::GetBool(*lines++, NAMEOF(_active), _active);
        _disableRotation = Serialization::GetBool(*lines++, NAMEOF(_disableRotation), _disableRotation);
        _disableTranslate = Serialization::GetBool(*lines++, NAMEOF(_disableTranslate), _disableTranslate);
        _disableScale = Serialization::GetBool(*lines++, NAMEOF(_disableScale), _disableScale);
        _name = Serialization::GetString(*lines++, NAMEOF(_name), _name);
        _position = Serialization::GetVetor3D(*lines++, NAMEOF(_position), _position);
        _rotation = Serialization::GetVetor3D(*lines++, NAMEOF(_rotation), _rotation);
        _scale = Serialization::GetVetor3D(*lines++, NAMEOF(_scale), _scale);
        lines++; //pulando definição
        while (!Serialization::EndOfArray(*lines)) 
        {
            Object* child = nullptr;
            switch (Serialization::GetType(*lines))
            {
            case EModel3D:
                child = new Model3D();
                break;
            case ECamera3D:
                child = new Camera3D();
                break;
            default:
                child = new Object();
                break;
            }
            _children.push_back(child->deserialize(lines));

        }

        lines++; //avançando ']'
    }
    
    

    return this;
}
