#ifndef OBJETO_H
#define OBJETO_H

#include "GL/gl.h"
#include "gui.h"
#include <iostream>
#include "Vetor3D.h"

typedef struct {
    float r,g,b,a;
    bool especular;
}Cor;

typedef struct {
    float x,y,z;
}Normal;

class Objeto{
    private:




        void initMouse();

    public:

        typedef enum {PlanoObj, CuboObj, CasaObj, CaixaObj} Tipo;


        Tipo tipo;
        float objtx; //Mouse direito
        float objty;
        float objtz;
        float objax; //Mouse esquerdo
        float objay;
        float objaz;
        float objex; // Mouse meio
        float objey;
        float objez;

        Vetor3D posicao;




        bool selecionado;
        bool eixoLocal;

        std::string nome;




        Cor cor;

        void setColor(float vermelho, float verde, float azul, float transparencia = 1.0, bool especular = false);
        void setColor(Cor cor);



        string set_nome(Vetor3D posicao, string nome);

        virtual void desenhar() = 0;
        virtual void inverter() = 0;

        void selecao();
        Objeto();
        Objeto(Cor cor);
        Objeto(float vermelho, float azul, float verde, float transparencia, bool especular);
        ~Objeto(){}
};

#endif // OBJETO_H
