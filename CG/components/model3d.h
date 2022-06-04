#ifndef MODEL3D_H
#define MODEL3D_H
#include "object.h"
#include "../bib/Vetor3D.h"
#include "../utils/material.h"
#include <glut.h>
#include <list>
#include <vector>
using namespace std;

class Model3D : public Object{



public:
    vector<Vetor3D> _lines;
	vector<Material*>  _materials;
    GLenum _mode;
	

	int getCycleSize()
	{
		switch (_mode) 
		{
			case GL_POLYGON:
				return INT16_MAX;
			case GL_TRIANGLES:
				return 3;
			case GL_QUADS:
				return 4;
			default:
				cout << "GLenum " << _mode << " não suportdado" << endl;
				return GL_TRIANGLES;
		}
	}

	static Model3D* Home(
		float floorWidth = 7.f,
		float floorDepth = 10.f,
		float wallHeight = 2.8f,
		float peakRelativeHeight = .5f) {

		return new Model3D(GL_TRIANGLES);
	}
	static Model3D* Table(
		float footerHeight = 1.f,
		float feetSize = .05f,
		float feetMargin = 0.5f,
		float surfaceWidth = 1.f,
		float surfaceDepth = 1.5f,
		float surfaceHeigth = .05f) {

		auto points = new list<Vetor3D>();

		auto feetStart = Vetor3D(-feetSize / 2.f, 0.f, -feetSize / 2.f);
		auto feetEnd = Vetor3D(feetSize / 2.f, footerHeight, feetSize / 2.f);

		

		//Pernas
		addBox(*points, 
			feetStart - Vetor3D(-(surfaceWidth - feetMargin)/2.f, 0, -(surfaceWidth - feetMargin) / 2.f),
			feetEnd - Vetor3D(-(surfaceWidth - feetMargin) / 2.f, 0, -(surfaceWidth - feetMargin) / 2.f));
		addBox(*points,
			feetStart - Vetor3D(-(surfaceWidth - feetMargin) / 2.f, 0, (surfaceWidth - feetMargin) / 2.f),
			feetEnd - Vetor3D(-(surfaceWidth - feetMargin) / 2.f, 0, (surfaceWidth - feetMargin) / 2.f));
		addBox(*points,
			feetStart + Vetor3D(-(surfaceWidth - feetMargin) / 2.f, 0, -(surfaceWidth - feetMargin) / 2.f),
			feetEnd + Vetor3D(-(surfaceWidth - feetMargin) / 2.f, 0, -(surfaceWidth - feetMargin) / 2.f));
		addBox(*points,
			feetStart + Vetor3D(-(surfaceWidth - feetMargin) / 2.f, 0, (surfaceWidth - feetMargin) / 2.f),
			feetEnd + Vetor3D(-(surfaceWidth - feetMargin) / 2.f, 0, (surfaceWidth - feetMargin) / 2.f));


		addBox(*points,
			Vetor3D(-surfaceWidth / 2.0f, footerHeight, -surfaceWidth / 2.0f),
			Vetor3D(surfaceWidth / 2.0f, footerHeight + surfaceHeigth, surfaceWidth / 2.0f));
		auto arrayPoints = new vector<Vetor3D>(begin(*points), end(*points));

		return new Model3D(GL_QUADS, *arrayPoints);
	}

	static Model3D* Plane(Vetor3D min, Vetor3D max) 
	{
		auto points = new list<Vetor3D>();

		points->push_back(Vetor3D(min.x, min.y, min.z));
		points->push_back(Vetor3D(max.x, min.y, min.z));
		points->push_back(Vetor3D(max.x, max.y, min.z));
		points->push_back(Vetor3D(min.x, max.y, min.z));
		
		auto arrayPoints = new vector<Vetor3D>(begin(*points), end(*points));

		return new Model3D(GL_QUADS, *arrayPoints);

	}

	
    
	void addBox(Vetor3D min, Vetor3D max, Material* material);
    
    virtual string serialize();
	virtual void draw();
	Model3D(GLenum mode, vector<Vetor3D>& lines, vector<Material*>* materials = nullptr, bool randomColors = true);
    Model3D(GLenum mode, bool randomColors = true);
    ~Model3D();
};

#endif // MODEL3D_H
