#ifndef PLANO_H
#define PLANO_H
#include "Vetor3D.h"
#include "Objeto.h"

class Plano : public Objeto{

    public:

        float tamanho_x, tamanho_z;
        Normal *normal;
        void desenhar();
        void inverter();

        Plano();
        Plano(Vetor3D posicao, float tamanho_x, float tamanho_z);
};

#endif // PLANO_H
