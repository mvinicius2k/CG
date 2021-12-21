#ifndef CAIXA_H
#define CAIXA_H

#include "Cubo.h"
#include "Vetor3D.h"

class Caixa : public Objeto{
    private:
        const float X_CAIXA = 10;
        float tamanho;
        Cubo* cubo;

    public:


        void desenhar();
        void inverter();


        Caixa(float tamanho);
};

#endif // CAIXA_H
