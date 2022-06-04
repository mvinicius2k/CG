#ifndef MODEL3D_H
#define MODEL3D_H
#include "object.h"
#include "../bib/Vetor3D.h"
#include "../utils/material.h"
#include <glut.h>
#include <list>
#include <vector>
#include "../utils/color.h"


using namespace std;

class Model3D : public Object{



public:
    vector<Vetor3D> _lines, _normals;
	vector<Material*>  _materials;
    GLenum _mode;
	
	

	int getCycleSize();
	
	

	static Model3D* Home(
		float floorWidth = 7.f,
		float floorDepth = 10.f,
		float wallHeight = 2.8f,
		float peakRelativeHeight = .5f,
		Material* wallMaterial = nullptr,
		Material* ceilMaterial = nullptr) {

		

		auto walls = Model3D::Box(Vetor3D(0, 0, 0), Vetor3D(floorWidth, wallHeight, -floorDepth), wallMaterial);
		auto ceil = new Model3D(GL_TRIANGLES);

		auto ceilPoints = vector<Vetor3D>(18);
		auto ceilNormals = vector<Vetor3D>(4);

		//Frente
		ceilPoints.push_back(Vetor3D(0, wallHeight, 0));
		ceilPoints.push_back(Vetor3D(floorWidth, wallHeight, 0));
		ceilPoints.push_back(Vetor3D(floorWidth, wallHeight + peakRelativeHeight, 0));
		ceilNormals.push_back(Vetor3D(0, 0, 1));


		ceil->_lines.insert(ceil->_lines.end(), ceilPoints.begin(), ceilPoints.end());
		
		ceil->_materials.push_back(ceilMaterial);

		
		walls->_childs.push_back(ceil);




		return walls;
	}

	

	static Model3D* Box(Vetor3D min, Vetor3D max, Material* material = nullptr)
	{
		auto box = new Model3D(GL_QUADS);

		box->addBox(min, max);
		box->_materials.push_back(material);

		return box;
	}

	static Model3D* SimpleTable(
		Material* material = nullptr,
		float footerHeight = 1.f,
		float feetSize = .05f,
		float feetMargin = 0.5f,
		float surfaceWidth = 1.f,
		float surfaceDepth = 1.5f,
		float surfaceHeigth = .05f
		) {

		auto model = new Model3D(GL_QUADS);

		auto points = new list<Vetor3D>();

		auto feetStart = Vetor3D(-feetSize / 2.f, 0.f, -feetSize / 2.f);
		auto feetEnd = Vetor3D(feetSize / 2.f, footerHeight, feetSize / 2.f);

		model->_materials.push_back(material);


		//Pernas
		model->addBox(
			feetStart - Vetor3D(-(surfaceWidth - feetMargin)/2.f, 0, -(surfaceWidth - feetMargin) / 2.f),
			feetEnd - Vetor3D(-(surfaceWidth - feetMargin) / 2.f, 0, -(surfaceWidth - feetMargin) / 2.f));
		model->addBox(
			feetStart - Vetor3D(-(surfaceWidth - feetMargin) / 2.f, 0, (surfaceWidth - feetMargin) / 2.f),
			feetEnd - Vetor3D(-(surfaceWidth - feetMargin) / 2.f, 0, (surfaceWidth - feetMargin) / 2.f));
		model->addBox(
			feetStart + Vetor3D(-(surfaceWidth - feetMargin) / 2.f, 0, -(surfaceWidth - feetMargin) / 2.f),
			feetEnd + Vetor3D(-(surfaceWidth - feetMargin) / 2.f, 0, -(surfaceWidth - feetMargin) / 2.f));
		model->addBox(
			feetStart + Vetor3D(-(surfaceWidth - feetMargin) / 2.f, 0, (surfaceWidth - feetMargin) / 2.f),
			feetEnd + Vetor3D(-(surfaceWidth - feetMargin) / 2.f, 0, (surfaceWidth - feetMargin) / 2.f));


		model->addBox(
			Vetor3D(-surfaceWidth / 2.0f, footerHeight, -surfaceWidth / 2.0f),
			Vetor3D(surfaceWidth / 2.0f, footerHeight + surfaceHeigth, surfaceWidth / 2.0f));
		

		return model;
	}

	
    
	void addBox(Vetor3D min, Vetor3D max);
    
    virtual string serialize();
	virtual void draw();
	Model3D(GLenum mode, vector<Vetor3D>& lines, vector<Material*>* materials = nullptr, bool randomColors = true);
    Model3D(GLenum mode, bool randomColors = true);
    ~Model3D();
};

#endif // MODEL3D_H
