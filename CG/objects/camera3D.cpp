#include "camera3D.h"

void Camera3D::use()
{
	if (currentCam == nullptr)
		defaultCam = glutGUI::cam;
	else
		currentCam->_camModel->_active = _active;

	glutGUI::cam = new CameraDistante(_position, _aim, _up);
	currentCam = this;
	_camModel->_active = false;
}

void Camera3D::draw()
{
	if (currentCam == this)
	{
		glutGUI::cam->e = _position;
	}
}





Camera3D::Camera3D(Vetor3D eye, Vetor3D aim, Vetor3D up)
{
	_position = eye;
	_aim = aim;
	_up = up;

	_disableRotation = _disableScale = true;

	_camModel = Model3D::Camera();
	_children.push_back(_camModel);

}

Camera3D::~Camera3D()
{
	UseDefaultCam();
	delete _camModel;
}
