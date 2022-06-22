#include "camera3D.h"
#include <utils/strings.h>
#include <utils/serialization.h>
void Camera3D::use()
{
	if (currentCam == nullptr)
		defaultCam = glutGUI::cam;
	else
		currentCam->_camModel->_active = _active;

	glutGUI::cam = new CameraDistante(_position, _aim, _up);
	currentCam = this;
	_camModel->_active = false;

	auto vetor = _aim;
	vetor.normaliza();


}



void Camera3D::draw()
{
	if (currentCam == this)
	{
		glutGUI::cam->e = _position;
	}
}

string Camera3D::serialize()
{
	auto object = stringstream();
	object << typeid(Camera3D).name() << endl
		<< NAMEOF(_aim) << "=" << Strings::Vector3DToString(_aim) << endl
		<< NAMEOF(_up) << "=" << Strings::Vector3DToString(_up) << endl
		<< Object::serialize() << endl
		;
	return object.str();
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

void Camera3D::update()
{
	if (currentCam != nullptr)
	{
		glutGUI::cam->c = _aim;

	}
}

Camera3D* Camera3D::deserialize(std::vector<std::string>::iterator& lines)
{
	if (Serialization::LineIsObject(*lines++, *this))
	{
		_aim = Serialization::GetVetor3D(*lines++, NAMEOF(_aim), _aim);
		_up = Serialization::GetVetor3D(*lines++, NAMEOF(_up), _up);
		
		Object::deserialize(lines);
	}

	return this;
}
