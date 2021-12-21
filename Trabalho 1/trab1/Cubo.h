#ifndef CUBO_H
#define CUBO_H
#include "Objeto.h"
#include "Vetor3D.h"

class Cubo : public Objeto{
    private:


    public:
        float tamanho;

        void desenhar();
        void inverter();

        Cubo();
        Cubo(Vetor3D posicao, float tamanho);
};



#endif // CUBO_H
