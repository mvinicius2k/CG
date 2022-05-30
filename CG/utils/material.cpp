#include "material.h"

Material::Material(Color color, bool especular, Vetor3D normal)
{
	_color = color;
	_especular = especular;
	_normal = normal;
}

