#pragma once
#include "../gui_glut/extra.h";

using namespace std;

class Mouse
{
private:

public:
	inline static int _lastX, _lastY;



	static void MouseMotion(int x, int y)
	{
		
			glutGUI::dtx = 0.0; glutGUI::dty = 0.0; glutGUI::dtz = 0.0;
			glutGUI::dax = 0.0; glutGUI::day = 0.0; glutGUI::daz = 0.0;
			glutGUI::dsx = 0.0; glutGUI::dsy = 0.0; glutGUI::dsz = 0.0;
		
	}
};