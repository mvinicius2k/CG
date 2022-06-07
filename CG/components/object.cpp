
#include "object.h"
#include <windows.h>
#include "../gui_glut/gui.h"
#include <string>
#include "../utils/strings.h"
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
        GUI::drawOrigin(true || _drawOriginSize);
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
    _position.x = glutGUI::tx;
    _position.y = glutGUI::ty;
    _position.z = glutGUI::tz;

    _rotation.x = glutGUI::ax;
    _rotation.y = glutGUI::ay;
    _rotation.z = glutGUI::az;

    _scale.x = glutGUI::sx;
    _scale.y = glutGUI::sy;
    _scale.z = glutGUI::sz;

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

string Object::serialize() {
    return "";
}
