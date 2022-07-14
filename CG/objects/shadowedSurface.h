#pragma once
#include <objects/model3d.h>

class ShadowedSurface : public Object
{
private:
	vector<Object*>* _objects;
public:
	Vetor3D _normal = Vetor3D(0, 1, 0);
	Model3D* _surface = Model3D::Box(Vetor3D(-10, -1, -10), Vetor3D(10, 0, 10));

	ShadowedSurface(vector<Object*>* objects)
	{
		_objects = objects;
		_disableRotation = _disableScale = _disableTranslate = true;
	}
	void setSelected(bool value, bool selectedByParent = false) override;
	virtual void draw();
private:

};

