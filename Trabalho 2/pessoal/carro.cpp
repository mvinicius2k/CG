#include "carro.h"

Carro::Carro()
{
    model = new Model3DS("3ds/cartest.3DS");
}

void Carro::desenha()
{
    glPushMatrix();
        Objeto::desenha();

        glScalef(1,1,1.2);
        glRotatef(-90,1,0,0);
        glTranslatef(0,0,0);
        glScalef(0.001,0.001,0.001);
        //model->draw();
        if (selecionado) {
            GUI::setColor(0.0,0.5,0.5);
            model->draw(false);
        } else {
            //GUI::setColor(1,1,0);
            model->draw();
        }

    glPopMatrix();
}
