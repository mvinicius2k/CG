#include <texture/material.h>
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
		<< NAMEOF(_color) << "=" << endl << _color.serialize()
		<< NAMEOF(_especular) << "=" << to_string(_especular) << endl
		;

	return object.str();
}


Material* Material::deserialize(std::vector<std::string>::iterator& lines)
{
	auto color = new Color();
	if (Serialization::LineIsObject(*lines++, *this))
	{
		_color = *color->deserialize(++lines);
		_especular = Serialization::GetBool(*lines++, NAMEOF(_especular), _especular);
		
	}

	return this;
}


