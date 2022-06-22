#pragma once
#include "object.h"
#include "model3d.h"
#include "../bib/Vetor3D.h"
#include "../gui_glut/gui.h"


class Camera3D : public Object
{
private:
	inline static int Id = 0;
	static inline auto defaultCam = glutGUI::cam;
	static inline Camera3D* currentCam = nullptr;
	bool used;
protected:
	Model3D* _camModel;
public:



	Vetor3D _aim; //centro
	Vetor3D _up;


	static void UseDefaultCam()
	{
		if (currentCam != nullptr)
		{
			currentCam->_camModel->_active = currentCam->_active;
			currentCam = nullptr;
			glutGUI::cam = defaultCam;
		}
	}
	static Camera3D* GetCurrentCam()
	{
		return currentCam;
	}
	void use();
	virtual void draw();
	virtual string serialize() override;
	
	Camera3D(Vetor3D eye = Vetor3D(0,0,0), Vetor3D aim = Vetor3D(1, 0, 0), Vetor3D up = Vetor3D(0, 1, 0));
	~Camera3D();
	void update();
	virtual Camera3D* deserialize(std::vector<std::string>::iterator& lines) override;
};