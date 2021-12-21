#include "Caixa.h"

Caixa::Caixa(float tamanho)
{
    this->posicao = Vetor3D(0,0,0);
    this->tipo = CaixaObj;
    this->setColor(0.8,0.8,0.8);
    this->tamanho = tamanho;
    nome = "Caixa ";

    this->cubo = new Cubo(this->posicao, this->tamanho);

}

void Caixa::desenhar(){



   // cubo->desenhar();

    selecao();

    glBegin(GL_QUADS);

        //Face de frente

    glNormal3f(0, 0, 1);
    glVertex3f(posicao.x + tamanho/X_CAIXA,posicao.y,posicao.z + tamanho/X_CAIXA);
    glVertex3f(posicao.x + tamanho,posicao.y + tamanho - tamanho/X_CAIXA,posicao.z+ tamanho/X_CAIXA);
    glVertex3f(posicao.x + tamanho - tamanho/X_CAIXA,posicao.y + tamanho,posicao.z+ tamanho/X_CAIXA);
    glVertex3f(posicao.x, posicao.y + tamanho/X_CAIXA,posicao.z+ tamanho/X_CAIXA);

    glEnd();
    glPushMatrix();

            glTranslatef(-(tamanho/X_CAIXA)/2,0,(tamanho/X_CAIXA)/2);
            glRotatef(90, 1,1,0);


            glBegin(GL_QUADS);
                glNormal3f(0, 0, 1);
                glVertex3f(posicao.x + tamanho/X_CAIXA,posicao.y,posicao.z + tamanho/X_CAIXA);
                glVertex3f(posicao.x + tamanho,posicao.y + tamanho - tamanho/X_CAIXA,posicao.z+ tamanho/X_CAIXA);
                glVertex3f(posicao.x + tamanho - tamanho/X_CAIXA,posicao.y + tamanho,posicao.z+ tamanho/X_CAIXA);
                glVertex3f(posicao.x, posicao.y + tamanho/X_CAIXA,posicao.z+ tamanho/X_CAIXA);

            glEnd();
    glPopMatrix();
    glPushMatrix();

            glTranslatef(-tamanho/X_CAIXA/2,0,tamanho/X_CAIXA/2);
            glRotatef(-90, 1,1,0);


            glBegin(GL_QUADS);
                glNormal3f(0, 0, 1);
                glVertex3f(posicao.x + tamanho/X_CAIXA,posicao.y,posicao.z + tamanho/X_CAIXA);
                glVertex3f(posicao.x + tamanho,posicao.y + tamanho - tamanho/X_CAIXA,posicao.z+ tamanho/X_CAIXA);
                glVertex3f(posicao.x + tamanho - tamanho/X_CAIXA,posicao.y + tamanho,posicao.z+ tamanho/X_CAIXA);
                glVertex3f(posicao.x, posicao.y + tamanho/X_CAIXA,posicao.z+ tamanho/X_CAIXA);

            glEnd();
    glPopMatrix();





        Objeto::desenhar();



    glPopMatrix();

}

void Caixa::inverter(){

}


