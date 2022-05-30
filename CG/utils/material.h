#ifndef MATERIAL_H
#define MATERIAL_H
#include "color.h"
#include "../bib/Vetor3D.h"

using namespace std;

class Material
{
public:
    Color _color ;
    bool _especular;
    Vetor3D _normal;
    static Material* White() 
    {
        return new Material(Color::White(), false, Vetor3D(1, 1, 1));
    }
    static Material* Random()
    {
        return new Material(Color::Random(), false, Vetor3D(1, 1, 1));
    }
    Material(Color color, bool especular, Vetor3D normal);
};

#endif // MATERIAL_H
