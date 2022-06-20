#pragma once
#include "object.h"
#include "../bib/Vetor3D.h"
#include <texture/material.h>
#include <glut.h>
#include <list>
#include <vector>
#include <texture/color.h>


using namespace std;

class Model3D : public Object{

protected:
	void addBox(Vetor3D min, Vetor3D max);

public:
    vector<Vetor3D> _lines, _normals;
	vector<Material*>  _materials;
    GLenum _mode;
	
	

	int getCycleSize();
	void centralize();

	static Model3D* Home(float floorWidth = 7.f,float floorDepth = 10.f,float wallHeight = 2.8f,float peakRelativeHeight = .5f,	Material* wallMaterial = Material::Default(),
		Material* ceilMaterial = Material::Default(),	bool centralize = true) 
	{

		auto xMiddle = (floorWidth / 2.f);
		auto yPeak = wallHeight + peakRelativeHeight;



		auto walls = Model3D::Box(Vetor3D(0, 0, 0), Vetor3D(floorWidth, wallHeight, floorDepth), wallMaterial);
		auto ceil = new Model3D(GL_QUADS, "Teto");
		auto ceilFrontBack = new Model3D(GL_TRIANGLES, "Paredes do teto");

		walls->_name = "Paredes";
		{ //normais do teto inclinado
			auto leftNormal = Vetor3D(0, 0, floorDepth).prodVetorial(Vetor3D(xMiddle, peakRelativeHeight,0));
			auto rightNormal = leftNormal;
			rightNormal.x *= -1.f;
			leftNormal.normaliza();
			rightNormal.normaliza();
			ceil->_normals.push_back(leftNormal);
			ceil->_normals.push_back(rightNormal);
		}

		


		auto ceilPoints = vector<Vetor3D> {
			Vetor3D(0, wallHeight, 0),
			Vetor3D(0, wallHeight, floorDepth),
			Vetor3D(xMiddle, yPeak, floorDepth),
			Vetor3D(xMiddle, yPeak, 0),

			Vetor3D(floorWidth, wallHeight, 0),
			Vetor3D(xMiddle, yPeak, 0),
			Vetor3D(xMiddle, yPeak, floorDepth),
			Vetor3D(floorWidth, wallHeight, floorDepth),
		};

		ceil->_materials.push_back(ceilMaterial);

		auto ceilFrontBackPoints = vector<Vetor3D>{

			//Trazeira
			Vetor3D(0, wallHeight, 0),
			Vetor3D(xMiddle, yPeak, 0),
			Vetor3D(floorWidth, wallHeight, 0),

			//Frente
			Vetor3D(0, wallHeight, floorDepth),
			Vetor3D(floorWidth, wallHeight, floorDepth),
			Vetor3D(xMiddle, yPeak, floorDepth),
		};

		ceilFrontBack->_normals.push_back(Vetor3D(0, 0, -1));
		ceilFrontBack->_normals.push_back(Vetor3D(0, 0, 1));

		ceilFrontBack->_materials.push_back(ceilMaterial);

		


		ceil->_lines.insert(ceil->_lines.end(), ceilPoints.begin(), ceilPoints.end());
		ceilFrontBack->_lines.insert(ceilFrontBack->_lines.end(), ceilFrontBackPoints.begin(), ceilFrontBackPoints.end());

		
		walls->_children.push_back(ceil);
		walls->_children.push_back(ceilFrontBack);

		if (centralize)
		{
			ceil->centralize();
			ceilFrontBack->centralize();
			walls->centralize();
		}
			
		return walls;
	}

	

	static Model3D* Box(Vetor3D min, Vetor3D max, Material* material = Material::Default(), bool centralizeXZ = true)
	{
		auto box = new Model3D(GL_QUADS, "Caixa");

		

		box->addBox(min, max);

		box->_materials.push_back(material);

		box->centralize();

		return box;
	}

	static Model3D* SimpleTable(Material* material = Material::Default(), float footerHeight = 1.f, float feetSize = .05f, float feetMargin = 0.5f,
		float surfaceWidth = 1.f, float surfaceDepth = 1.5f,float surfaceHeigth = .05f, bool centralize = true)
	{

		auto model = new Model3D(GL_QUADS, "Mesa simples");

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
		
		if(centralize)
			model->centralize();
		return model;
	}

	static Model3D* Pyramid(Material* material = Material::Default(), float baseSize = .5f, float distance = .5f, bool centralize = true)
	{

		auto model = new Model3D(GL_TRIANGLES, "Pirâmide");

		auto points = vector<Vetor3D>
		{
			//base
			Vetor3D(baseSize,0,baseSize),
			Vetor3D(0,0,baseSize),
			Vetor3D(0,0,0),
			Vetor3D(0,0,0),
			Vetor3D(baseSize,0,0),
			Vetor3D(baseSize,0,baseSize),

			//trás
			Vetor3D(0,0,0),
			Vetor3D(baseSize / 2.f,distance,baseSize / 2.f),
			Vetor3D(baseSize,0,0),
			//frente
			Vetor3D(baseSize,0,baseSize),
			Vetor3D(baseSize / 2.f,distance,baseSize / 2.f),
			Vetor3D(0,0,baseSize),
			//esquerda
			Vetor3D(0,0,baseSize),
			Vetor3D(baseSize / 2.f,distance,baseSize / 2.f),
			Vetor3D(0,0,0),
			//direita
			Vetor3D(baseSize,0,0),
			Vetor3D(baseSize / 2.f,distance,baseSize / 2.f),
			Vetor3D(baseSize,0,baseSize),
		};

		auto leftNormal = Vetor3D(0, 0, -baseSize).prodVetorial(Vetor3D(-baseSize, -distance, 0));
		leftNormal.normaliza();
		auto rightNormal = leftNormal;
		rightNormal.x *= -1.f;
		auto backNormal = Vetor3D(-baseSize, 0, 0).prodVetorial(Vetor3D(0, -distance, baseSize));
		backNormal.normaliza();
		auto frontNormal = backNormal;
		backNormal.z *= -1.f;

		auto normals = vector<Vetor3D>{
			Vetor3D(0,-1,0),
			Vetor3D(0,-1,0),
			backNormal,
			frontNormal,
			leftNormal,
			rightNormal
		};
		
		model->_materials.push_back(material);
		model->_lines.insert(model->_lines.end(), points.begin(), points.end());
		model->_normals.insert(model->_normals.end(), normals.begin(), normals.end());
		
		if (centralize)
			model->centralize();


		return model;
	}
    
	static Model3D* Camera(Material* bodyMaterial = Material::Default(), Material* lensMaterial = Material::Default(), float bodySize = .5f, bool centralize = true)
	{
		
		auto body = Model3D::Box(Vetor3D(0, 0, 0), Vetor3D(bodySize, bodySize, bodySize), bodyMaterial);
		auto lens = Model3D::Pyramid(lensMaterial, bodySize / 1.5f, bodySize / 1.5f);

		lens->_rotation.z = 90.f;
		lens->_position.x += bodySize;
		lens->_position.y += bodySize/ 2.f;

		body->_children.push_back(lens);

		return body;
	}
    
    string serialize();
	static Model3D* deserialize(string& str)
	{
		return nullptr;
	}
	static Model3D* Deserialize(vector<string>::iterator& it)
	{

	}
	
	virtual void draw();
	Model3D(GLenum mode, string name = "Modelo 3D");
    ~Model3D();
};



