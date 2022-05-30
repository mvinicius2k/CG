#include "model3d.h"
#include "../gui_glut/gui.h"

using namespace std;



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

