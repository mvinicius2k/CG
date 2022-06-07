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
    
    static Material* Default()
    {
        return Material::Random();
    }

    static Material* White() 
    {
        return new Material(Color::White(), false);
    }
    static Material* Random()
    {
        return new Material(Color::Random(), true);
    }
    Material(Color color, bool especular);
};

#endif // MATERIAL_H
