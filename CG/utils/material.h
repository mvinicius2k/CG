#ifndef MATERIAL_H
#define MATERIAL_H
#include "color.h"
#include "../bib/Vetor3D.h"

using namespace std;

class Material
{
public:
    Color _color;
    bool _especular;
    Vetor3D _normal;

    Material();
};

#endif // MATERIAL_H
