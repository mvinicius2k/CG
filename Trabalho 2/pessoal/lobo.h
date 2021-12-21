#ifndef LOBO_H
#define LOBO_H

#include <objeto.h>

class Lobo : public Objeto
{
public:
    Model3DS* model;
public:
    Lobo();
    void desenha();
};

#endif // LOBO_H
