#include <windows.h>
#include <cstdio>
#include <sstream>
#include <iostream>
#include "bib/Camera.h"
#include "gui_glut/gui.h"
#include "components/object.h"
#include <vector>
#include "components/model3d.h"
#include "main.h"
#include "utils/mouse.h"



using namespace std;

const char ADD_TABLE = '1';
const char TRANSLATE = 'w';
const char ROTATE = 'e';
const char SCALE = 'r';
const char NEXT_OBJ = 'd';
const char PREVIOUS_OBJ = 'a';
const char REMOVE_OBJ = 127; //Delete
const char SAVE_SCENE = 'S';
const char RELOAD_SCENE = 'R';

const char TOGGLE_OBJECT_INFO = 'i';
const char DESELECT = '\'';

//Model3DS carro = Model3DS("/3ds/cartest.3DS");


auto objects = vector<Object*>();
int currentIndex = -1;
bool displayObjectInfos = false;;



void modeloTeste()
{

	//face traseira
	//glDisable(GL_CULL_FACE);
	glPushMatrix();
	//static float rot = 0;
	//rot += 0.2;
	//glRotatef(rot, 1,1,0);
	glRotatef(180, 1, 1, 0);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	glPopMatrix();
	//glEnable(GL_CULL_FACE);

	//face inferior
	glPushMatrix();
	glRotatef(180, 1, 0, 1);
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 0);
	glEnd();
	glPopMatrix();

	//face esquerda
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 0);
	glEnd();
	glPopMatrix();

	//face frontal
	glPushMatrix();
	glTranslatef(0, 0, 1);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	glPopMatrix();

	//face direita
	glPushMatrix();
	//testamos diferentes composições de transformações
	glTranslatef(1, 0, 0);
	glTranslatef(0, 0, 1);
	glRotatef(90, 0, 1, 0);
	//GUI::drawOrigin(0.5);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	glPopMatrix();

	//face superior
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, -1, 1);
	//GUI::drawOrigin(0.5);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	glPopMatrix();


	//face telhado esquerdo
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, -1, 1);
	glRotatef(45, 0, -1, 0);
	glTranslatef(-0.29, 0, 0);
	//GUI::drawOrigin(0.5);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	glPopMatrix();

	//face telhado direito
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, -1, 1);
	glTranslatef(1, 0, 0);
	glRotatef(-45, 0, -1, 0);
	glTranslatef(-0.71, 0, 0);
	//GUI::drawOrigin(0.5);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	glPopMatrix();

	//    //face inclinada
	//    glBegin( GL_POLYGON );
	//        glNormal3f( 1,1,0 );
	//        glVertex3f( 0,1,0 );
	//        glVertex3f( 0,1,1 );
	//        glVertex3f( 1,0,1 );
	//        glVertex3f( 1,0,0 );
	//    glEnd();
	//    glTranslatef( 0,1,0 );
	//    glRotatef( -45, 0,0,1 );
	//    glBegin( GL_POLYGON );
	//        glNormal3f( 0,1,0 );
	//        glVertex3f( 0,0,0 );
	//        glVertex3f( 0,0,1 );
	//        glVertex3f( 1,0,1 );
	//        glVertex3f( 1,0,0 );
	//    glEnd();
}


float esferaPosX = 0;
float esferaPosY = 0;
float esferaRotZ = 0;
float esferaEscX = 1;
float esferaEscY = 1;

float caixaPosX = 0;
float caixaPosY = 0;
float caixaPosZ = 0;
float caixaRotX = 0;
float caixaRotY = 0;
float caixaRotZ = 0;
float caixaEscX = 1;
float caixaEscY = 1;
float caixaEscZ = 1;

bool caixa = true;
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

		current->offAllTransformActions();
		current->setSelected(false);
		currentIndex = (currentIndex + 1) % objects.size();
		
	}
	else
		currentIndex = 0;

	current = objects.at(currentIndex);
	current->setSelected(false);
	current->_showInfos = displayObjectInfos;
}

void selectPreviousObject()
{
	if (objects.size() <= 0)
		return;

	auto current = getSelectedObject();
	if (current != nullptr)
	{

		current->offAllTransformActions();
		current->setSelected(false);
		currentIndex = (currentIndex - 1) % objects.size();

	}
	else
		currentIndex = objects.size() -1;

	current = objects.at(currentIndex);
	current->setSelected(false);
	current->_showInfos = displayObjectInfos;
}


void init()
{

	/*auto table = Model3D::Table();
	objects.push_back(table);*/

}

void desenha()
{



	GUI::displayInit();

	if (!_initialized)
	{
		init();
		_initialized = true;
	}

	

	//GUI::setLight(0,  0,1,0, true); //,false);
	//GUI::setLight(1,  1,1,0, true); //,false);
	//GUI::setLight(2, -1,1,0, true); //,false);
	//GUI::setLight(3,  0,0.5,0, true); //,false);

	GUI::setLight(0, 3, 5, 4, true, false);

	GUI::drawOrigin(0.5);
	GUI::setColor(1, 0, 0, 1, true);
	//GUI::drawFloor(5,5,0.1,0.1);
	GUI::drawFloor();
	//consoleLog(to_string(glutGUI::dtx));

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
	case 't':
		glutGUI::trans_obj = !glutGUI::trans_obj;
		break;
	case 's':
		caixa = !caixa;
		break;


	case ADD_TABLE:
		objects.push_back(Model3D::Table());
		consoleLog(string("Mesa adicionada na posiçao ").append(to_string(objects.size() - 1)));
		break;

	case NEXT_OBJ:
		
		selectNextObject();
		consoleLog(string("Objecto ").append(to_string(currentIndex)).append(" selecionado"));
		break;
	case PREVIOUS_OBJ:
		selectPreviousObject();
		consoleLog(string("Objecto ").append(to_string(currentIndex)).append(" selecionado"));
		break;

	case DESELECT:
	{
		auto current = getSelectedObject();
		if (current != nullptr)
		{
			current->offAllTransformActions();
			current->setSelected(false);
			glutGUI::trans_obj = false;

		}
		break;
	}
	case ROTATE:
	{
		auto current = getSelectedObject();
		if (current != nullptr)
		{
			current->offAllTransformActions();
			current->_rotate = true;
			glutGUI::trans_obj = true;
			consoleLog(string("Rotação para ")
				.append(to_string(currentIndex)));

		}
		break;
	}
	case TRANSLATE: 
	{
		auto current = getSelectedObject();
		if (current != nullptr)
		{
			current->offAllTransformActions();
			current->_translate = true;
			glutGUI::trans_obj = true;
			consoleLog(string("Translação para ")
				.append(to_string(currentIndex)));

		}
		break;
	}
	case SCALE:
	{
		auto current = getSelectedObject();
		if (current != nullptr)
		{
			current->offAllTransformActions();
			current->_escalete = true;
			glutGUI::trans_obj = true;
			consoleLog(string("Escala para")
				.append(to_string(currentIndex)));

		}
		break;
	}
	case TOGGLE_OBJECT_INFO:
	{
		displayObjectInfos = !displayObjectInfos;
		auto current = getSelectedObject();
		if (current != nullptr)
			current->_showInfos = displayObjectInfos;
		consoleLog(string("Mostrar informações do objeto: ")
			.append(to_string(displayObjectInfos)));
	}
		
		//case 'w':
		//    esferaPosY += 0.2;
		//    break;
		//case 's':
		//    esferaPosY -= 0.2;
		//    break;
		//case 'a':
		//    esferaPosX -= 0.2;
		//    break;
		//case 'd':
		//    esferaPosX += 0.2;
		//    break;
		//case 'r':
		//    esferaRaio *= 0.5;
		//    break;
		//case 'R':
		//    esferaRaio *= 2;
		//    break;
	default:
		break;
	}
}







int main(int argc, char** argv)
{
	SetConsoleOutputCP(CP_UTF8);

	
	cout << "Hello World!" << endl;
	//GUI gui();
	GUI gui = GUI(800, 600, desenha, teclado, glutGUI::defaultMouseButton, "CG", argc, argv);



	
}



//inicializando OpenGL
//while(true) {
//    desenha();
//    interacaoUsuario();
//    //if () {
//    //    break;
//    //}
//}




//Espelhamento

//glPushMatrix();
//    //caixa
//    glTranslatef( caixaPosX, caixaPosY, caixaPosZ );
//    glRotatef( caixaRotX, 1,0,0 );
//    glRotatef( caixaRotY, 0,1,0 );
//    glRotatef( caixaRotZ, 0,0,1 );
//    glScalef( caixaEscX, caixaEscY, caixaEscZ );
//    GUI::drawOrigin(0.5);
//    GUI::setColor(0,0,1, 1,true);
//    modeloTeste();
//glPopMatrix();
//glDisable(GL_CULL_FACE);
//glPushMatrix();
//    GUI::glReflectPlaneXYf();
//    //interpretacao:
//    //                 -----> local
//    //                 <----- global
//    //vert_saida = I . T . R . vert_entrada
//    glTranslatef( caixaPosX, caixaPosY, caixaPosZ );
//    glRotatef( caixaRotX, 1,0,0 );
//    glRotatef( caixaRotY, 0,1,0 );
//    glRotatef( caixaRotZ, 0,0,1 );
//    glScalef( caixaEscX, caixaEscY, caixaEscZ );
//    //GUI::glShearXZf( caixaPosX, caixaPosZ );
//    //GUI::glShearYZf( caixaPosY, caixaPosZ );
//    //GUI::glShearXYf( caixaPosX, caixaPosY );
//    //GUI::glShearXf( caixaPosY, caixaPosZ );
//    //caixa
//    GUI::drawOrigin(0.5);
//    GUI::setColor(0,0,1, 1,true);
//    modeloTeste();
//    //desfazendo as tranformações locais do 3ds
//    //glScalef(1,1,1);
//    //glRotatef(-90, 1,0,0);
//    //glTranslatef(0,0,0);
//    //glScalef(0.0005,0.0005,0.0005);
//    //carro.draw();
//glPopMatrix();
//glEnable(GL_CULL_FACE);
