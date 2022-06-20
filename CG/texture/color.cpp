#include "color.h"
#include <utils/serialization.h>

using namespace std;
Color::Color()
{
}
Color::Color(float r, float g, float b, float a)
{
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}



Color::~Color()
{
}

string Color::serialize()
{
	auto object = stringstream();
	object << typeid(Color).name() << endl
		<< NAMEOF(_r) << "=" << to_string(_r) << endl
		<< NAMEOF(_g) << "=" << to_string(_g) << endl
		<< NAMEOF(_b) << "=" << to_string(_b) << endl
		<< NAMEOF(_a) << "=" << to_string(_a) << endl;
		

	return object.str();
}





//Color* Color::deserialize(std::string& str)
//{
//	return nullptr;
//}
//
//string Color::serialize()
//{
//	auto object = stringstream();
//	object << typeid(Color).name() << "{" << endl
//		<< NAMEOF(_r) << "=" << to_string(_r) << endl
//		<< NAMEOF(_g) << "=" << to_string(_r) << endl
//		<< NAMEOF(_b) << "=" << to_string(_b) << endl
//		<< NAMEOF(_a) << "=" << to_string(_a) << endl
//		<< "}";
//
//	return object.str();
//}
