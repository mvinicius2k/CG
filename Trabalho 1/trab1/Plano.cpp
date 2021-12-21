#include "Plano.h"
#include "Objeto.h"
#include "Vetor3D.h"
#include "gui.h"

Plano::Plano() : Objeto(){
    nome = "Plano ";
    tipo = PlanoObj;

}



Plano::Plano(Vetor3D posicao, float tamanho_x, float tamanho_z) : Objeto(){
    std::string nome = "Plano";
    this->nome = set_nome(posicao, "Plano");

    this->posicao = posicao;


    this->tamanho_x = tamanho_x;
    this->tamanho_z = tamanho_z;

    this->setColor(0.8,0.8,0.8);
    this->tipo = PlanoObj;
}

void Plano::desenhar(){




        if(selecionado)
            GUI::setColor(1,1,1);
        else
            GUI::setColor(cor.r,cor.g,cor.b, cor.a, cor.especular);


        //Face de cima
        glBegin(GL_QUADS);
            glNormal3f(0, 1, 0);
            glVertex3f(posicao.x,posicao.y,posicao.z);
            glVertex3f(posicao.x, posicao.y,posicao.z + tamanho_z);
            glVertex3f(posicao.x + tamanho_x,posicao.y,posicao.z + tamanho_z);
            glVertex3f(posicao.x + tamanho_x,posicao.y,posicao.z);
        glEnd();

        //Face de baixo
        glBegin(GL_QUADS);
            glNormal3f(0, -1, 0);
            glVertex3f(posicao.x,posicao.y,posicao.z);
            glVertex3f(posicao.x + tamanho_x,posicao.y,posicao.z);
            glVertex3f(posicao.x + tamanho_x,posicao.y,posicao.z + tamanho_z);
            glVertex3f(posicao.x, posicao.y,posicao.z + tamanho_z);
        glEnd();


        glPushMatrix();
        //Transformações
            Objeto::desenhar();
        glPopMatrix();





}



void Plano::inverter(){

}

