#include <windows.h>
#include <cstdio>
#include <sstream>
#include <cmath>
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

using namespace std;


auto objects = vector<Object*>();
auto cameras = vector<Camera3D*>{
	new Camera3D(Vetor3D(-2,1,0),Vetor3D(0,0,0)),
	new Camera3D(Vetor3D(-22,1,0),Vetor3D(0,0,0))
};
int currentIndex = -1;
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
	objects.insert(objects.end(), cameras.begin(), cameras.end());
}

void desenha()
{
	GUI::displayInit();

	if (!_initialized)
	{
		init();
		_initialized = true;
	}


	


	GUI::setLight(0, 3, 5, 4, true, false);

	GUI::drawOrigin(0.5);

	for (auto object : objects)
	{
		object->render();
	}


	GUI::displayEnd();
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
	case K_ADD_CAMERA_MODEL:
		objects.push_back(Model3D::Camera());
		consoleLog(string("Modelo 3D de câmera adicionada na posiçao ").append(to_string(objects.size() - 1)));
		break;
	case K_ADD_CAMERA:
		objects.push_back(new Camera3D());
		consoleLog(string("Câmera adicionada na posição ").append(to_string(objects.size() - 1)));
		break;
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
		

		bool founded = false;

		for (int i = currentCam+1; i < objects.size(); i++)
		{
			auto camera = static_cast<Camera3D*>(objects[i]);
			if (camera != nullptr)
			{
				camera->use();
				founded = true;
				currentCam = i;
				break;
			}
		}
		
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

	case K_DESELECT:
	{
		deselect();
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
	
	cout << "Hello World! " << endl << &color;
	
	GUI gui = GUI(800, 600, desenha, teclado, glutGUI::defaultMouseButton, "CG", argc, argv);

}
