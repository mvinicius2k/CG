#pragma once
#include "color.h"
#include "../bib/Vetor3D.h"



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

    

   


    // Herdado por meio de Serializable
    std::string serialize();

    static Material* Deserialize(std::string& str)
    {
        return nullptr;
    }

};

