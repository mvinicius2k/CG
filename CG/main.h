#pragma once
static inline const char K_ADD_TABLE = '1';
static inline const char K_ADD_HOUSE = '2';
static inline const char K_ADD_BOX = '3';
static inline const char K_ADD_PYRAMID = '4';
static inline const char K_ADD_CAMERA_MODEL = '5';
static inline const char K_TRANSFORM_OBJECT = 't';

static inline const char K_NEXT_OBJ = 'd';
static inline const char K_PREVIOUS_OBJ = 'a';
static inline const char K_REMOVE_OBJ = 127; //Delete
static inline const char K_NEXT_CAM = 'c';
static inline const char K_DEFAULT_CAM = 'v';

static inline const char K_SAVE_SCENE = 'S';
static inline const char K_RELOAD_SCENE = 'R';

static inline const char K_TOGGLE_OBJECT_INFO = 'i';
static inline const char K_DESELECT = '\'';

static inline const string SAVE_FILENAME = "save.cg";

void desenha();

void teclado(unsigned char tecla, int mouseX, int mouseY);

int deselect();

int main(int argc, char** argv);

void consoleLog(string str);

Object* getSelectedObject();

void selectNextObject();

void selectPreviousObject();
