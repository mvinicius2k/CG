#pragma once
static inline const char K_ADD_TABLE = '1';
static inline const char K_ADD_HOUSE = '2';
static inline const char K_ADD_BOX = '3';
static inline const char K_ADD_PYRAMID = '4';
static inline const char K_ADD_CAMERA_MODEL = '5';
static inline const char K_ADD_CAMERA = '6';
static inline const char K_ADD_SHADOWED_PLANE = '7';
static inline const char K_CAMERA_LOOK_TO = 'b';
static inline const char K_TRANSFORM_OBJECT = 't';
static inline const char K_TOGGLE_SHADOW = 'y';
static inline const char K_TOGGLE_SHADOW_ALL = 'Y';
static inline const char K_TOGGLE_INFINITY_LIGHT = 'j';
static inline const char K_TOGGLE_RENDER_PROJ = 'p';

static inline const char K_NEXT_OBJ = 'd';
static inline const char K_PREVIOUS_OBJ = 'a';
static inline const char K_REMOVE_OBJ = 127; //Delete
static inline const char K_DUPLICATE_OBJ = 'h';
static inline const char K_NEXT_CAM = 'c';
static inline const char K_DEFAULT_CAM = 'v';

static inline const char K_SAVE_SCENE = 'S';
static inline const char K_LOAD_SCENE = 'L';

static inline const char K_TOGGLE_OBJECT_INFO = 'i';
static inline const char K_DESELECT = '\'';
static inline const char K_DECREASE_GRID = '-';
static inline const char K_INCREASE_GRID = '=';
static inline const char K_DECREASE_RGRID = '_';
static inline const char K_INCREASE_RGRID = '+';
static inline const char K_TOGGLE_GRID = '[';


enum class ProjKind
{
	Perspective, Orthografic
};


static vector<Object*> objects;

static inline const string SAVE_FILENAME = "save.cg";

void desenha();

void renderObjects();

void teclado(unsigned char tecla, int mouseX, int mouseY);

int deselect();

int main(int argc, char** argv);

void consoleLog(string str);

Object* getSelectedObject();

void selectNextObject();

void selectPreviousObject();
