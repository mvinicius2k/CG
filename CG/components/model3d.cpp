#include "model3d.h"
#include <vector>
#include "../gui_glut/gui.h"

using namespace std;



int Model3D::getCycleSize()
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



void Model3D::addBox(Vetor3D min, Vetor3D max)
{
	auto vmin = Vetor3D(min(min.x, max.x), min(min.y,max.y), min(min.z, max.z));
	auto vmax = Vetor3D(max(min.x, max.x), max(min.y, max.y), max(min.z, max.z));

	if (getCycleSize() != 4)
		throw exception("Somente glquads");

	auto pointList = vector<Vetor3D>(48);
	auto normalList = vector<Vetor3D>(6);

	//Base
	pointList.push_back(Vetor3D(
		vmin.x,
		vmin.y,
		vmin.z));
	pointList.push_back(Vetor3D(
		vmax.x,
		vmin.y,
		vmin.z
	));
	pointList.push_back(Vetor3D(
		vmax.x,
		vmin.y,
		vmax.z
	));
	pointList.push_back(Vetor3D(
		vmin.x,
		vmin.y,
		vmax.z
	));
	normalList.push_back(Vetor3D(0, 1, 0));

	//Teto
	pointList.push_back(Vetor3D(
		vmin.x,
		vmax.y,
		vmin.z));
	pointList.push_back(Vetor3D(
		vmin.x,
		vmax.y,
		vmax.z
	));
	pointList.push_back(Vetor3D(
		vmax.x,
		vmax.y,
		vmax.z
	));
	pointList.push_back(Vetor3D(
		vmax.x,
		vmax.y,
		vmin.z
	));
	normalList.push_back(Vetor3D(0, -1, 0));

	//Fundo
	pointList.push_back(Vetor3D(
		vmin.x,
		vmin.y,
		vmin.z));
	pointList.push_back(Vetor3D(
		vmin.x,
		vmax.y,
		vmin.z
	));
	pointList.push_back(Vetor3D(
		vmax.x,
		vmax.y,
		vmin.z
	));
	pointList.push_back(Vetor3D(
		vmax.x,
		vmin.y,
		vmin.z
	));
	normalList.push_back(Vetor3D(0, 0, 1));

	//Frente
	pointList.push_back(Vetor3D(
		vmin.x,
		vmin.y,
		vmax.z));
	pointList.push_back(Vetor3D(
		vmax.x,
		vmin.y,
		vmax.z
	));
	pointList.push_back(Vetor3D(
		vmax.x,
		vmax.y,
		vmax.z
	));
	pointList.push_back(Vetor3D(
		vmin.x,
		vmax.y,
		vmax.z
	));
	normalList.push_back(Vetor3D(0, 0, -1));

	//Direita
	pointList.push_back(Vetor3D(
		vmax.x,
		vmin.y,
		vmin.z));
	pointList.push_back(Vetor3D(
		vmax.x,
		vmax.y,
		vmin.z
	));
	pointList.push_back(Vetor3D(
		vmax.x,
		vmax.y,
		vmax.z
	));
	pointList.push_back(Vetor3D(
		vmax.x,
		vmin.y,
		vmax.z
	));
	normalList.push_back(Vetor3D(-1, 0, 0));

	//Esquerda
	pointList.push_back(Vetor3D(
		vmin.x,
		vmin.y,
		vmin.z
	));
	pointList.push_back(Vetor3D(
		vmin.x,
		vmin.y,
		vmax.z
	));
	pointList.push_back(Vetor3D(
		vmin.x,
		vmax.y,
		vmax.z
	));
	pointList.push_back(Vetor3D(
		vmin.x,
		vmax.y,
		vmin.z
	));
	normalList.push_back(Vetor3D(1, 0, 0));

	this->_lines.insert(_lines.end(), pointList.begin(), pointList.end());
	this->_normals.insert(_normals.end(), normalList.begin(), normalList.end());
	
	
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
			if (i % cycle == 0 && _materials.size() != 0) {
				auto material =  _materials.at(i % _materials.size());
				auto selectedLight = _selected ? 0.4f : 0.0f;

				auto normal = _normals.size() != 0 ? _normals.at(i % _normals.size()) : Vetor3D(1, 1, 1);

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

