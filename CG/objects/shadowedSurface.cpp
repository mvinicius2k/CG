#include "shadowedSurface.h"
#include <scene/light.h>
#include <utils/math.h>

void ShadowedSurface::draw()
{
	if (_objects == 0) 
	{
		cout << "sem objetos " << endl;
		return;
	}
	_surface->render();


	auto lightPosition = Light::GetPosition();
	
	GLfloat lightData[] = {
		lightPosition.x, lightPosition.y , lightPosition.z, (int)Light::Kind
	};

	float shadowMatrix[4][4];
	


	
	//auto lightDirection = Vetor3D(sinf(_surface->_rotation.z/2.f), cos(_surface->_rotation.y), sinf(_surface->_rotation.x/2.f));
	glDisable(GL_LIGHTING);
	glColor3d(0.0, 0.0, 0.0);
	GUI::shadowMatrix(shadowMatrix, _normal, 0.005f, lightData);
	Math::Transposef(shadowMatrix);
	glMultMatrixf((GLfloat*)shadowMatrix);
	//glMultTransposeMatrixf(shadowMatrix);

	
	glPushMatrix();
	
	
	//glTranslatef(_position.x, _surface->_position.y, _position.z);
	//glRotatef(_surface->_rotation.x, 1, 0, 0);
	//glRotatef(_surface->_rotation.y, 0, 1, 0);
	//glRotatef(_surface->_rotation.z, 0, 0, 1);
	
	for (auto object : *_objects)
	{
		auto self = dynamic_cast<ShadowedSurface*>(object);
		if(self == nullptr && !object->_disableShadow)
			object->render();
	}
	glEnable(GL_LIGHTING);

	glPopMatrix();
	

	

}

void ShadowedSurface::setSelected(bool value, bool selectedByParent)
{
	Object::setSelected(value, selectedByParent);
	_surface->setSelected(value);
}

