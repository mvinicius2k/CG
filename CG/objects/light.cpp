#include "light.h"
#include <gui_glut/gui.h>
void Light::draw()
{
	

	for (auto object : objectsToShadow) 
	{

	}
}

void Light::addLight()
{
	
	GUI::setLight(_id, _position.x, _position.y, _position.z, true, false);
	//GUI::setLight(_id, _position.x+5, _position.y, _position.z, true, false);
}

Light::Light(Vetor3D position, float range)
{
	_position = position;
	_range = range;
	_disableScale = _disableRotation = true;
	_id = ++LastId;
	addLight();
}
