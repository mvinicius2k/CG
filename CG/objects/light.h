#pragma once
#include <objects/object.h>
#include <vector>
#include <objects/model3d.h>
class Light : public Object
{
protected:
	inline static int LastId = -1;
	float _range;
	int _id;
	void addLight();
public:
	vector<Model3D*> objectsToShadow;
	bool drawShadows;
	
	virtual void draw();
	Light(Vetor3D position = Vetor3D(0,0,0), float range = 5.f);
};

