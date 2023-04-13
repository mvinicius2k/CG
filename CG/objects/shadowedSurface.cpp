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

	//Contém uma superfície por padrão. Aqui a renderiza e desenha
	_surface->render();


	auto lightPosition = Light::GetPosition();
	
	GLfloat lightData[] = {
		lightPosition.x, lightPosition.y , lightPosition.z, (int)Light::Kind
	};

	float shadowMatrix[4][4];
	
	glDisable(GL_LIGHTING);
	glColor3d(0.0, 0.0, 0.0);
	GUI::shadowMatrix(shadowMatrix, _normal, 0.005f, lightData);
	Math::Transposef(shadowMatrix); 
	glMultMatrixf((GLfloat*)shadowMatrix); 
	//glMultTransposeMatrixf(shadowMatrix); //esse glMultTransposeMatrixf é do glew, por algum motivo misterioso das profundezas dá erro de seguimentação de todoas as formas que tentei

	
	glPushMatrix();
	
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

