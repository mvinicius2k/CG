#include "Cubo.h"
#include "Objeto.h"

Cubo::Cubo() : Objeto()
{
    nome = "Cubo ";
    tipo = CuboObj;
    this->setColor(0.8,0.8,0.8);
}



Cubo::Cubo(Vetor3D posicao, float tamanho) : Objeto(){
    this->nome = set_nome(posicao, "Cubo");

    this->posicao = posicao;
    this->tamanho = tamanho;

    this->setColor(0.8,0.8,0.8);
    this->tipo = CuboObj;

}

void Cubo::desenhar(){



        selecao();

        glBegin(GL_QUADS);

            //Face de frente

            glNormal3f(0, 0, 1);
            glVertex3f(posicao.x,posicao.y,posicao.z);
            glVertex3f(posicao.x + tamanho,posicao.y,posicao.z);
            glVertex3f(posicao.x + tamanho,posicao.y + tamanho,posicao.z);
            glVertex3f(posicao.x, posicao.y + tamanho,posicao.z);

            //Face de cima
            glNormal3f(0, 1, 0);
            glVertex3f(posicao.x + tamanho,posicao.y + tamanho,posicao.z);
            glVertex3f(posicao.x + tamanho,posicao.y + tamanho,posicao.z - tamanho);
            glVertex3f(posicao.x,posicao.y + tamanho,posicao.z - tamanho);
            glVertex3f(posicao.x,posicao.y + tamanho,posicao.z);

            //Face de trás
            glNormal3f(0, 0, -1);
            glVertex3f(posicao.x, posicao.y + tamanho,posicao.z - tamanho);
            glVertex3f(posicao.x + tamanho,posicao.y + tamanho,posicao.z - tamanho);
            glVertex3f(posicao.x + tamanho,posicao.y,posicao.z - tamanho);
            glVertex3f(posicao.x,posicao.y,posicao.z - tamanho);

            //Face de baixo
            glNormal3f(0, -1, 0);
            glVertex3f(posicao.x,posicao.y,posicao.z);
            glVertex3f(posicao.x,posicao.y,posicao.z - tamanho);
            glVertex3f(posicao.x + tamanho,posicao.y,posicao.z - tamanho);
            glVertex3f(posicao.x + tamanho,posicao.y,posicao.z);


            //Face da esquerda
            glNormal3f(-1, 0, 0);
            glVertex3f(posicao.x,posicao.y,posicao.z);
            glVertex3f(posicao.x,posicao.y + tamanho,posicao.z);
            glVertex3f(posicao.x,posicao.y + tamanho,posicao.z - tamanho);
            glVertex3f(posicao.x, posicao.y,posicao.z - tamanho);

            //Face da direita
            glNormal3f(1, 0, 0);
            glVertex3f(posicao.x + tamanho, posicao.y,posicao.z - tamanho);
            glVertex3f(posicao.x + tamanho,posicao.y + tamanho,posicao.z - tamanho);
            glVertex3f(posicao.x + tamanho,posicao.y + tamanho,posicao.z);
            glVertex3f(posicao.x + tamanho,posicao.y,posicao.z);







        glEnd();
    glPushMatrix();


        Objeto::desenhar();



    glPopMatrix();
}

void Cubo::inverter(){

}
