#ifndef COLOR_H
#define COLOR_H
#include <Windows.h>
#include <random>
#include "serializable.h"

using namespace std;

class Color : Serializable<Color>
{
private:
    static float get_random()
    {
        static std::default_random_engine e;
        static std::uniform_real_distribution<> dis(0, 1); // rage 0 - 1
        return dis(e);
    }
public:
    float _r,_g,_b,_a;
    static Color Random()
    {
        auto color = Color(get_random(), get_random(), get_random(), 1.f);
        return color;
    }
    static Color White() {
        return Color(1.f, 1.f, 1.f, 1.f);
    }
    Color(float r, float g, float b, float a);
    Color();
    ~Color();

    

    // Herdado por meio de Serializable
    virtual string serialize() override;

    virtual Color* deserialize(std::string& str);

};

#endif // COLOR_H
