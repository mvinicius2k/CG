#include "model3d.h"
#include <vector>
#include "../gui_glut/gui.h"
#include <limits>
#include <string>
#include <sstream>
#include "../utils/strings.h"
#include <utils/serialization.h>
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

	auto normalList = vector<Vetor3D>{
		Vetor3D(0, -1, 0),
		Vetor3D(0, 1, 0),
		Vetor3D(0, 0, -1),
		Vetor3D(0, 0, 1),
		Vetor3D(1, 0, 0),
		Vetor3D(-1, 0, 0)
	};
	auto pointList = vector<Vetor3D>{
		//base
		Vetor3D( vmin.x, vmin.y, vmin.z),
		Vetor3D(vmax.x,	vmin.y,	vmin.z),
		Vetor3D(vmax.x,	vmin.y,	vmax.z),
		Vetor3D(vmin.x,	vmin.y,	vmax.z),

		//teto
		Vetor3D(vmin.x,vmax.y, vmin.z),
		Vetor3D(vmin.x,	vmax.y,	vmax.z),
		Vetor3D(vmax.x, vmax.y,	vmax.z),
		Vetor3D(vmax.x,	vmax.y,	vmin.z),

		//Fundo
		Vetor3D(vmin.x,	vmin.y,	vmin.z),
		Vetor3D(vmin.x,	vmax.y,	vmin.z),
		Vetor3D(vmax.x,	vmax.y,	vmin.z),
		Vetor3D(vmax.x,	vmin.y,	vmin.z),

		//Frente
		Vetor3D(vmin.x,	vmin.y,	vmax.z),	
		Vetor3D(vmax.x,	vmin.y,	vmax.z),
		Vetor3D(vmax.x,	vmax.y,	vmax.z),
		Vetor3D(vmin.x,	vmax.y,	vmax.z),
	
		//Direita
		Vetor3D(vmax.x,	vmin.y,	vmin.z),
		Vetor3D(vmax.x,	vmax.y,	vmin.z),
		Vetor3D(vmax.x,	vmax.y,	vmax.z),
		Vetor3D(vmax.x,	vmin.y,	vmax.z),

		//Esquerda
		Vetor3D(vmin.x,	vmin.y,	vmin.z),
		Vetor3D(vmin.x,	vmin.y,	vmax.z),
		Vetor3D(vmin.x,	vmax.y,	vmax.z),
		Vetor3D(vmin.x,	vmax.y,	vmin.z)
	};

	
	
	

	

	

	

	this->_lines.insert(_lines.end(), pointList.begin(), pointList.end());
	this->_normals.insert(_normals.end(), normalList.begin(), normalList.end());
	
}



void Model3D::centralize()
{
	auto constexpr fmax = (numeric_limits<float>::max)();
	auto constexpr fmin = (numeric_limits<float>::min)();

	auto min = Vetor3D(fmax, fmax, fmax);
	auto max = Vetor3D(fmin, fmin, fmin);

	for (auto point : _lines)
	{

		if (point.x < min.x)
			min.x = point.x;
		if (point.z < min.z)
			min.z = point.z;

		if (point.x > max.x)
			max.x = point.x;
		if (point.z > max.z)
			max.z = point.z;
	}

	auto xTranslate = (min.x + max.x) / 2.f;
	auto zTranslate = (min.z + max.z) / 2.f;

	for (int i = 0; i < _lines.size(); i++)
	{
		_lines[i] = Vetor3D(_lines[i].x - xTranslate, _lines[i].y, _lines[i].z - zTranslate);
	}
	


}

void Model3D::draw()
{
	if (!_active)
		return;
	auto cycle = getCycleSize();

     

	glBegin(_mode); 
	{
		for (int i = 0; i < _lines.size(); i++)
		{
			if (i % cycle == 0) {

				//Definindo cor
				Material* material;
				int materialI = -1;
				if (_materials.size() > 0)
				{
					materialI = (i / cycle) % _materials.size();
					material = _materials.at(materialI);
				}
				else
				{
					material = Material::Default();
					consoleLog("Sem material, usando padrão");
				}
				
				auto selectedLight = _selected ? 0.4f : 0.0f;
				
				GUI::setColor(
					material->_color._r + selectedLight,
					material->_color._g + selectedLight,
					material->_color._b + selectedLight,
					material->_color._a,
					material->_especular);

				//Definindo normais
				Vetor3D normal;
				int normalI = -1;
				if (_normals.size() > 0)
				{
					normalI = (i / cycle) % _normals.size();
					normal = _normals.at(normalI);
				}
				else
					consoleLog("Sem normal, usando (1,1,1)");
				

				glNormal3f(normal.x, normal.y, normal.z);
			}
			glVertex3f(_lines.at(i).x, _lines.at(i).y, _lines.at(i).z);
			
		}
			

	} glEnd();
}

Model3D::Model3D(GLenum mode, string name) : Object(name)
{
	_mode = mode;
	_lines = vector<Vetor3D>();
	_materials = vector<Material*>();
}









Model3D::~Model3D() 
{
	
}

string Model3D::serialize()
{
	auto object = stringstream();
	object << typeid(Model3D).name() << endl
		<< NAMEOF(_mode) << "=" << to_string(_mode) << endl
		<< NAMEOF(_lines) << "=" << Serialization::Vectors3DToString(_lines) << endl
		<< NAMEOF(_normals) << "=" << Serialization::Vectors3DToString(_normals) << endl
		<< NAMEOF(_materials) << "=" << Serialization::MaterialsToString(_materials) << endl
		<< Object::serialize();
	;
	return object.str();
}

Model3D* Model3D::deserialize(std::vector<std::string>::iterator& lines)
{

	if (Serialization::LineIsObject(*lines++, *this))
	{
		_mode = Serialization::GetInt(*lines++, NAMEOF(_mode), _mode);

		lines++;
		while (!Serialization::EndOfArray(*lines)) 
		{
			auto line = Serialization::GetVetor3D(*lines++);
			_lines.push_back(line);
		}
		lines += 2; //pulando o '] e definição'
		while (!Serialization::EndOfArray(*lines))
		{
			auto normal = Serialization::GetVetor3D(*lines++);
			_normals.push_back(normal);
		}
		lines += 2; //pulando o '] e definição'
		while (!Serialization::EndOfArray(*lines))
		{
			
			auto material = new Material();
			material->deserialize(lines);
			_materials.push_back(material);
		}
		lines++; //pulando ']'
		Object::deserialize(lines);

	}

	return this;
}

