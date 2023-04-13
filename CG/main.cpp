#include <windows.h>
#include <cstdio>
#include <sstream>
#include <cmath>
#include <GL/glew.h>
#include <iostream>
#include "bib/Camera.h"
#include "gui_glut/gui.h"
#include "objects/object.h"
#include <vector>
#include "objects/model3d.h"
#include "main.h"
#include "objects/camera3D.h"
#include "utils/persistence.h"
#include "utils/serialization.h"
#include "utils/mouse.h"
#include "scene/light.h"
#include "utils/math.h"
#include <objects/shadowedSurface.h>

using namespace std;



//index do objeto atual selecionado no array
int currentIndex = -1;
//camera também
int currentCam = -1;


bool _initialized = false;




void consoleLog(string str)
{
	cout << str << endl;
}

Object* getSelectedObject()
{
	if (currentIndex != -1 && objects.size() > 0)
	{
		auto current = objects.at(currentIndex);
		if (current->isSelected())
			return current;
		else
			return nullptr;


	}
	
	else
		return nullptr;
}

void selectNextObject()
{
	if (objects.size() <= 0)
		return;

	auto current = getSelectedObject();
	if (current != nullptr)
	{

		current->setSelected(false);
		currentIndex = (currentIndex + 1) % objects.size();
		
	}
	else
		currentIndex = 0;

	current = objects.at(currentIndex);
	current->setSelected(true);
}

void selectPreviousObject()
{
	if (objects.size() <= 0)
		return;

	auto current = getSelectedObject();
	if (current != nullptr)
	{

		current->setSelected(false);
		int nextIndex;
		if (currentIndex == 0)
			nextIndex = objects.size() - 1;
		else
			nextIndex = currentIndex - 1;
		currentIndex = nextIndex;

	}
	else
		currentIndex = objects.size() -1;

	current = objects.at(currentIndex);
	current->setSelected(true);
}

/// <summary>
/// 
/// </summary>
/// <returns>O index que foi desselecionado</returns>
int deselect()
{
	auto current = getSelectedObject();
	if (current != nullptr)
	{
		current->setSelected(false);
		glutGUI::trans_obj = false;

	}

	auto deselectedIndex = currentIndex;
	currentIndex = -1;
	return deselectedIndex;

}


void init()
{
	glClearColor(0, .2f, 1.f, 1);
	

}

void desenha()
{
	GUI::displayInit();
	if (!_initialized)
	{
		init();
		_initialized = true;
	}



	GUI::setLight(0, 0, 0, 0, true, false);

	GUI::drawOrigin(0.5);
	renderObjects();
	
	GUI::displayEnd();
}

void renderObjects()
{
	int i = 0;
	for (auto object : objects) 
	{
		glPushName(++i);
		object->render();
		glPopName();
	}
}

int picking(GLint cursorX, GLint cursorY, int w, int h)
{
	const int BUFSIZE = 512;
	GLuint selectBuf[BUFSIZE];

	GUI::pickingInit(cursorX, cursorY, w, h, selectBuf, BUFSIZE);
	GUI::displayInit();
	
	renderObjects();
	return GUI::pickingClosestName(selectBuf, BUFSIZE);
}

void mouse(int button, int state, int x, int y)
{
	GUI::mouseButtonInit(button, state, x, y);

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN) 
		{
			auto selectedId = picking(x, y, 1, 1);
			cout << currentIndex << " selecionado" << endl;
			if (selectedId != 0)
			{
				deselect();
				currentIndex = selectedId - 1;
				objects[currentIndex]->setSelected(true);
				glutGUI::lbpressed = false;
			}
		}
	}
}

void teclado(unsigned char tecla, int mouseX, int mouseY)
{

	GUI::keyInit(tecla, mouseX, mouseY);

	switch (tecla)
	{
	case 'l':
		glutGUI::trans_luz = !glutGUI::trans_luz;
		break;

	case K_ADD_TABLE:
		
		objects.push_back(Model3D::SimpleTable());
		consoleLog(string("Mesa adicionada na posiçao ").append(to_string(objects.size() - 1)));
		break;

	case K_ADD_HOUSE:
		objects.push_back(Model3D::Home());
		consoleLog(string("Casa adicionada na posiçao ").append(to_string(objects.size() - 1)));
		break;
	case K_ADD_BOX:
		objects.push_back(Model3D::Box(Vetor3D(0,0,0), Vetor3D(1,1,1)));
		consoleLog(string("Caixa adicionada na posiçao ").append(to_string(objects.size() - 1)));
		break;
	case K_ADD_PYRAMID:
		objects.push_back(Model3D::Pyramid());
		consoleLog(string("Pirâmide adicionada na posiçao ").append(to_string(objects.size() - 1)));
		break;
		glPushName(objects.size() + 1);
	case K_ADD_CAMERA_MODEL:
		objects.push_back(Model3D::Camera());
		consoleLog(string("Modelo 3D de câmera adicionada na posiçao ").append(to_string(objects.size() - 1)));
		break;
	case K_ADD_CAMERA:
		objects.push_back(new Camera3D());
		consoleLog(string("Câmera adicionada na posição ").append(to_string(objects.size() - 1)));
		break;
	case K_ADD_SHADOWED_PLANE:
	{

		auto surface = new ShadowedSurface(&objects);
		auto wall1 = new ShadowedSurface(&objects);
		auto wall2 = new ShadowedSurface(&objects);
		wall1->_normal = Vetor3D(0, 1, 1);
		wall1->_surface->_rotation = (Vetor3D(45, 0, 0));
		wall2->_surface->_rotation = (Vetor3D(0, 0, 45));
		wall2->_normal = Vetor3D(	-1, 1,0);
		objects.push_back(surface);
		objects.push_back(wall1);
		objects.push_back(wall2);
		consoleLog(string("Planos sombreáveis adicionados até na posição ").append(to_string(objects.size() - 1)));
		break;
	}
	case K_TOGGLE_INFINITY_LIGHT: 
	{
		if (Light::Kind == LightKind::pontual) 
		{
			glutGUI::pontual_light[0] = false;
			Light::Kind = LightKind::infinity;
		}
		else
		{
			glutGUI::pontual_light[0] = true;
			Light::Kind = LightKind::pontual;
		}
		break;
	}
	case K_NEXT_OBJ:
		
		selectNextObject();
		consoleLog(string("Objecto ").append(to_string(currentIndex)).append(" selecionado"));
		break;
	case K_PREVIOUS_OBJ:
		selectPreviousObject();
		consoleLog(string("Objecto ").append(to_string(currentIndex)).append(" selecionado"));
		break;
	
	case K_NEXT_CAM:
	{
		

		Camera3D* camera = nullptr;
		bool founded = false;
		int i = currentCam;
		int lastIndex = i;
		int cont = 0;
		do
		{
			auto index = ++i % objects.size();
			if (lastIndex == index)
				cont++;
			if (cont == 2)
				break;

			camera = dynamic_cast<Camera3D*>(objects[index]);
			if (camera != nullptr)
			{
				cout << "Câmera " << index << endl;;
				camera->use();
				founded = true;
				currentCam = index;
				break;
			}
		} while (camera == nullptr);

		
		if (!founded)
		{
			currentCam = -1;
			consoleLog("Não há câmeras");

		}

		break;

	}

	case K_DEFAULT_CAM: 
	{
		Camera3D::UseDefaultCam();
		currentCam = -1;
		break;
	}
	case K_CAMERA_LOOK_TO:
	{
		auto obj = getSelectedObject();
		auto currentCam = Camera3D::GetCurrentCam();
		if (obj != nullptr && currentCam != nullptr && currentCam != obj)
		{
			currentCam->_aim = obj->_position;
			currentCam->update();
		}
		break;

	}
	case K_REMOVE_OBJ: 
	{
		auto currentIndex = deselect();
		if (currentIndex >= 0)
		{
			auto current = getSelectedObject();
			objects.erase(objects.begin() + currentIndex);
			delete current;
			
		}
		break;
	}

	case K_TOGGLE_SHADOW:
	{
		auto obj = getSelectedObject();
		if (obj != nullptr) 
			obj->_disableShadow = !obj->_disableShadow;

		break;
	}
	case K_TOGGLE_SHADOW_ALL:
	{
		if (objects.size() == 0)
			break;

		for (auto obj : objects)
			obj->_disableShadow = !objects[0]->_disableShadow;

		break;
	}



	case K_DESELECT:
	{
		deselect();
		break;
	}
	

	case K_TRANSFORM_OBJECT:
	{
		
		auto current = getSelectedObject();
		if (current != nullptr)
		{
			
			glutGUI::trans_obj = true;
			consoleLog(string("Transformação para")
				.append(to_string(currentIndex)));

		}
		break;
	}
	case K_TOGGLE_OBJECT_INFO:
	{
		Object::ShowInfos = !Object::ShowInfos;
		break;
	}
	case K_TOGGLE_RENDER_PROJ:
	{
		glutGUI::perspective = !glutGUI::perspective;
		glutGUI::orthof = 0.05;
		break;
	}
	case K_TOGGLE_GRID:
		Mouse::Enabled = !Mouse::Enabled;
		break;
	case K_INCREASE_GRID:
		Mouse::IncreaseGrid();
		break;
	case K_DECREASE_GRID:
		Mouse::DecreaseGrid();
		break;
	case K_DECREASE_RGRID:
		Mouse::DecreaseRotationGrid();
		break;
	case K_INCREASE_RGRID:
		Mouse::IncreaseRotationGrid();
		break;
	case K_SAVE_SCENE:
	{
		auto allObjectsStr = stringstream();

		for (auto object : objects)
			allObjectsStr << object->serialize();

		Persistence::Save(SAVE_FILENAME, allObjectsStr.str());

		break;
	}
	case K_LOAD_SCENE:
	{
		objects.clear();
		auto text = *Persistence::Load(SAVE_FILENAME);
		auto it = text.begin();
		objects.clear();

		while (it != text.end()) 
		{
			int distance = std::distance(text.begin(), it);
			cout << "Deserializando objeto em " << distance << endl;

			if (Serialization::GetType(*it) == EModel3D) 
			{
				auto obj = new Model3D();
				objects.push_back(obj->deserialize(it));

			}
			else if(Serialization::GetType(*it) == ECamera3D)
			{
				auto obj = new Camera3D();
				objects.push_back(obj->deserialize(it));
			}

		}

		cout << objects.size() << " carregados com sucesso (ou não)" << endl;
		break;

	}
	
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	SetConsoleOutputCP(CP_UTF8);

	Color color = Color(1, 2, 3, 4);
	
	cout << "Hello World! " << endl;
	
	GUI gui = GUI(800, 600, desenha, teclado, mouse, "CG", argc, argv);

}
