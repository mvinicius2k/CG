#include "model3d.h"
#include "../gui_glut/gui.h"

using namespace std;



void Model3D::addBox(Vetor3D min, Vetor3D max, Material materials[6])
{
	auto pointList = vector<Vetor3D>(24);
	//Base
	pointList.push_back(Vetor3D(
		min.x,
		min.y,
		min.z));
	pointList.push_back(Vetor3D(
		max.x,
		min.y,
		min.z
	));
	pointList.push_back(Vetor3D(
		max.x,
		min.y,
		max.z
	));
	pointList.push_back(Vetor3D(
		min.x,
		min.y,
		max.z
	));

	//Teto
	pointList.push_back(Vetor3D(
		min.x,
		max.y,
		min.z));
	pointList.push_back(Vetor3D(
		min.x,
		max.y,
		max.z
	));
	pointList.push_back(Vetor3D(
		max.x,
		max.y,
		max.z
	));
	pointList.push_back(Vetor3D(
		max.x,
		max.y,
		min.z
	));

	//Fundo
	pointList.push_back(Vetor3D(
		min.x,
		min.y,
		min.z));
	pointList.push_back(Vetor3D(
		min.x,
		max.y,
		min.z
	));
	pointList.push_back(Vetor3D(
		max.x,
		max.y,
		min.z
	));
	pointList.push_back(Vetor3D(
		max.x,
		min.y,
		min.z
	));

	//Frente
	pointList.push_back(Vetor3D(
		min.x,
		min.y,
		max.z));
	pointList.push_back(Vetor3D(
		max.x,
		min.y,
		max.z
	));
	pointList.push_back(Vetor3D(
		max.x,
		max.y,
		max.z
	));
	pointList.push_back(Vetor3D(
		min.x,
		max.y,
		max.z
	));

	//Direita
	pointList.push_back(Vetor3D(
		max.x,
		min.y,
		min.z));
	pointList.push_back(Vetor3D(
		max.x,
		max.y,
		min.z
	));
	pointList.push_back(Vetor3D(
		max.x,
		max.y,
		max.z
	));
	pointList.push_back(Vetor3D(
		max.x,
		min.y,
		max.z
	));

	//Direita
	pointList.push_back(Vetor3D(
		min.x,
		min.y,
		min.z
	));
	pointList.push_back(Vetor3D(
		min.x,
		min.y,
		max.z
	));
	pointList.push_back(Vetor3D(
		min.x,
		max.y,
		max.z
	));
	pointList.push_back(Vetor3D(
		min.x,
		max.y,
		min.z
	));

	this->_lines.insert(_lines.end(), pointList.begin(), pointList.end());
	this->_materials.insert(ma.end(), pointList.begin(), pointList.end());
	
}

string Model3D::serialize() {
	return ""; 
}

void Model3D::draw()
{
	auto cycle = getCycleSize();

     

	glBegin(_mode); 
	{
		for (int i = 0; i < _lines.size(); i++)
		{
			if (i % cycle == 0 &&  _materials.size() != 0) {
				auto material =  _materials.at(i % _materials.size());
				auto selectedLight = _selected ? 0.4f : 0.0f;
				auto normal = material->_normal;
				glNormal3f(normal.x, normal.y, normal.z);
				GUI::setColor(
					material->_color._r + selectedLight,
					material->_color._g + selectedLight,
					material->_color._b + selectedLight,
					material->_color._a,
					material->_especular);
			}
			glVertex3f(_lines[i].x, _lines[i].y, _lines[i].z);
			
		}
			

	} glEnd();
}


Model3D::Model3D(GLenum mode, vector<Vetor3D>& lines, vector<Material*>* materials, bool randomColors)
{
	
	if (materials == nullptr) 
	{
		materials = new vector<Material*>();
		materials->push_back(Material::Random());
	}
		

	_mode = mode;
	_lines = lines;
	_materials = * materials;
}

Model3D::Model3D(GLenum mode, bool randomColors)
{

	_mode = mode;
	_lines = vector<Vetor3D>();
	_materials = vector<Material*>();
}





Model3D::~Model3D() 
{
	
}

