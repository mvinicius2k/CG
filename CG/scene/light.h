#pragma once
#include <bib/Vetor3D.h>
#include <gui_glut/gui.h>

enum class LightKind
{
	pontual = 1, infinity = 0
};

class Light
{
private:
	inline static LightKind Kind = LightKind::pontual;
public:



	static Vetor3D GetPosition()
	{
		return Vetor3D(glutGUI::lx, glutGUI::ly, glutGUI::lz);
	}
	static Vetor3D SetPosition(Vetor3D newPosition)
	{
		glutGUI::lx = newPosition.x;
		glutGUI::ly = newPosition.y;
		glutGUI::lz = newPosition.z;
	}

	static LightKind GetKind()
	{
		return Kind;
	}
	static void SetKind(LightKind value)
	{
		Kind = value;
		
	}

	

	
};
