#ifndef CASA_H
#define CASA_H

#include "Objeto.h"
#include "Vetor3D.h"

class Casa : public Objeto{
    private:


    public:


        void desenhar();
        void inverter();

        void corSecundariaIn();
        void corSecundariaOut();

        Casa();
};

#endif // CASA_H
