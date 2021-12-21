#include "Casa.h"

Casa::Casa() : Objeto()
{
    this->posicao = Vetor3D(0,0,0);
    this->tipo = CasaObj;
    this->setColor(0.8,0.8,0.8);
    nome = "Casa ";

}

void Casa::corSecundariaIn(){
    if(!selecionado)
        GUI::setColor(cor.r - 0.2, cor.g - 0.2, cor.b - 0.2);
}
void Casa::corSecundariaOut(){
    if(!selecionado)
        GUI::setColor(cor.r + 0.2, cor.g + 0.2, cor.b + 0.2);
}

void Casa::desenhar(){



    selecao();

    glBegin(GL_TRIANGLES);


        //Frente
        glNormal3f(0,0,1);
        glVertex3f(0,3,0);
        glVertex3f(5,3,0);
        glVertex3f(2.5,4,0);

        //Atrás
        glNormal3f(0,0,-1);
        glVertex3f(0,3,-7);
        glVertex3f(2.5,4,-7);
        glVertex3f(5,3,-7);

    glEnd();

    glBegin(GL_QUADS);

        //chao
        glNormal3f(0,-1,0);
        glVertex3f(0,0,-7);
        glVertex3f(5,0,-7);
        glVertex3f(5,0,0);
        glVertex3f(0,0,0);

        //Parede da frente
        glNormal3f(0,0,1);
        glVertex3f(5,0,0);
        glVertex3f(5,3,0);
        glVertex3f(0,3,0);
        glVertex3f(0,0,0);

        //Parede de trás
        glNormal3f(0,0,-1);
        glVertex3f(0,0,-7);
        glVertex3f(0,3,-7);
        glVertex3f(5,3,-7);
        glVertex3f(5,0,-7);

        //Parede da esquerda
        glNormal3f(-1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(0,3,0);
        glVertex3f(0,3,-7);
        glVertex3f(0,0,-7);

        //Parede da direita
        glNormal3f(1,0,0);
        glVertex3f(5,0,0);
        glVertex3f(5,0,-7);
        glVertex3f(5,3,-7);
        glVertex3f(5,3,0);


        corSecundariaIn();
        //Teto esquerdo
        glNormal3f(-1,1,0);
        glVertex3f(0,3,0);
        glVertex3f(2.5,4,0);
        glVertex3f(2.5,4,-7);
        glVertex3f(0,3,-7);

        //Teto esquerdo
        glNormal3f(1,1,0);
        glVertex3f(5,3,0);
        glVertex3f(5,3,-7);
        glVertex3f(2.5,4,-7);
        glVertex3f(2.5,4,0);

        corSecundariaOut();

        //GUI::setColor(cor.r + 0.2, cor.g + 0.2, cor.b + 0.2);


    glEnd();




    glPushMatrix();


        Objeto::desenhar();



    glPopMatrix();

}

void Casa::inverter(){

}
