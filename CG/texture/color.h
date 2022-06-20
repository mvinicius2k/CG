#pragma once
#include <Windows.h>
#include <random>


class Color
{
private:
    static float GetRandom()
    {
        static std::default_random_engine e;
        static std::uniform_real_distribution<> dis(0, 1); // rage 0 - 1
        return dis(e);
    }
public:
    float _r,_g,_b,_a;
    static Color Random()
    {
        auto color = Color(GetRandom(), GetRandom(), GetRandom(), 1.f);
        return color;
    }
    static Color White() {
        return Color(1.f, 1.f, 1.f, 1.f);
    }
    Color(float r, float g, float b, float a);
    Color();
    ~Color();   




    std::string serialize();

    static Color* Deserialize(std::string& str)
    {
        return nullptr;
    }


    // Herdado por meio de Base

};
