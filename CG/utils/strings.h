#pragma once
#include <Windows.h>
#include <glut.h>
#include <string>
#include <vector>
#include "../bib/Vetor3D.h"

class Strings
{
public:
	static void DrawString(float x, float y, float z, std::string text)
	{
		glRasterPos3f(x, y, z);

		for (auto c : text)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
		}
		
	}

	static std::string Vector3DToString(Vetor3D vector)
	{
		return std::string("(")
			.append(to_string(vector.x))
			.append("; ")
			.append(to_string(vector.y))
			.append("; ")
			.append(to_string(vector.z))
			.append(")");
			
	}


	static std::string MaterialsToString(vector<Material*> materials)
	{
		
		auto str = std::string("[");
		/*for (auto material : materials)
			str.append(material->serialize()).append(", ");*/

		return str.append("]");

	}

	
};

