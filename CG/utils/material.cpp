#include "material.h"
#include <sstream>
Material::Material(Color color, bool especular)
{
	_color = color;
	_especular = especular;
}


Material* Material::deserialize(std::string str)
{
	return nullptr;
}

string Material::serialize()
{
	auto object = stringstream();
	object << typeid(Material).name() << "{" << endl
		<< NAMEOF(_color) << "=" << _color.serialize() << endl
		<< NAMEOF(_especular) << "=" << to_string(_especular) << endl
		<< "}";

	return object.str();
}


