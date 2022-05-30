#pragma once
#include <Windows.h>
#include <glut.h>
#include <string>
#include "../bib/Vetor3D.h"

using namespace std;
class Strings
{
public:
	static void DrawString(float x, float y, float z, string text)
	{
		glRasterPos3f(x, y, z);

		for (auto c : text)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
		}
		
	}

	static string Vector3DToString(Vetor3D vector)
	{
		return string("(")
			.append(to_string(vector.x))
			.append("; ")
			.append(to_string(vector.y))
			.append("; ")
			.append(to_string(vector.z))
			.append(")");
			
	}
};

