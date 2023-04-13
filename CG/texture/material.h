#pragma once
#include <texture/color.h>
#include <utils/serializable.h>
#include "../bib/Vetor3D.h"

//Engloba a cor e alguns elementos de superfície. Implementei somente se é especular ou não, mas pode ser usado também para escrever outras propriedades que definiriam como o objeto interage com a luz
class Material : Serializable<Material>
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
    Material(Color color = Color::Random(), bool especular = false);

    

   



    static Material* Deserialize(std::string& str)
    {
        return nullptr;
    }


    // Herdado por meio de Serializable
    virtual std::string serialize() override;

    virtual Material* deserialize(std::vector<std::string>::iterator& lines) override;

};

