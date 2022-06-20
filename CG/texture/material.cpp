#include "material.h"
#include <sstream>
#include <utils/serialization.h>

using namespace std;

Material::Material(Color color, bool especular)
{
	_color = color;
	_especular = especular;
}




string Material::serialize()
{
	auto object = stringstream();
	object << typeid(Material).name() << endl
		<< NAMEOF(_color) << "=" << _color.serialize() << endl
		<< NAMEOF(_especular) << "=" << to_string(_especular) << endl
		;

	return object.str();
}


