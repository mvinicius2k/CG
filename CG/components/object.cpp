
#include "object.h"
#include <windows.h>
#include "../gui_glut/gui.h"
using namespace std;

Object::Object()
{

    _active = true;



}

Object::~Object() {

}


void Object::draw()
{
    glTranslatef(_position.x, _position.y, _position.z);
    glRotatef(_rotation.x, 1,0,0);
    glRotatef(_rotation.y, 0, 1, 0);
    glRotatef(_position.z, 0, 0, 1);
    GUI::drawOrigin(_drawOriginSize);
    glScalef(_scale.x, _scale.y, _scale.z);
}

void Object::mouseInput()
{
    if(!_selected)
        return;

    _position.x += glutGUI::dtx;
    _position.y += glutGUI::dty;
    _position.z += glutGUI::dtz;

    _rotation.x += glutGUI::dax;
    _rotation.y += glutGUI::day;
    _rotation.z += glutGUI::daz;

    _scale.x += glutGUI::dsx;
    _scale.y += glutGUI::dsy;
    _scale.z += glutGUI::dsz;
}
