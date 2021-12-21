#include "Objeto.h"
#include "gui.h"
#include <sstream>
#include <string>

void Objeto::initMouse(){
    objtx = 0.0; //Mouse direito
    objty = 0.0;
    objtz = 0.0;
    objax = 0.0; //Mouse esquerdo
    objay = 0.0;
    objaz = 0.0;
    objex = 1.0; // Mouse meio
    objey = 1.0;
    objez = 1.0;
}

void Objeto::selecao(){
    if(selecionado)
        GUI::setColor(1,1,1);
    else
        GUI::setColor(cor.r,cor.g,cor.b, cor.a, cor.especular);
}

Objeto::Objeto()
{
    selecionado = eixoLocal = false;
    initMouse();


}

Objeto::Objeto(float vermelho, float azul, float verde, float transparencia, bool especular)
{
    selecionado = eixoLocal = false;

    cor.r = vermelho;
    cor.b = azul;
    cor.g = verde;
    cor.a = transparencia;
    cor.especular = especular;
    initMouse();

}

Objeto::Objeto(Cor cor)
{
    selecionado = false;
    this->setColor(cor);
    initMouse();
}


void Objeto::setColor(float r, float g, float b, float a, bool especular){
    this->cor.r = r;
    this->cor.g = g;
    this->cor.b = b;
    this->cor.a = a;
    this->cor.especular = especular;
}

void Objeto::setColor(Cor cor){
    this->setColor(cor.r, cor.g, cor.b, cor.a, cor.especular);
}

void Objeto::desenhar(){
    if(selecionado){
        objtx += glutGUI::dtx;
        objty += glutGUI::dty;
        objtz += glutGUI::dtz;
        objax += glutGUI::dax;
        objay += glutGUI::day;
        objaz += glutGUI::daz;
        objex += glutGUI::dsx;
        objey += glutGUI::dsy;
        objez += glutGUI::dsz;
    }


    if(eixoLocal)
        GUI::drawOrigin(0.5);
    /*
    glPushMatrix();
        glTranslatef(objtx, objty, objtz);
        glRotatef(objaz, 0, 0, 1);
        glRotatef(objay, 0, 1, 0);
        glRotatef(objax, 1, 0, 0);
    //
        glScalef(glutGUI::sx, glutGUI::sy, glutGUI::sz);
    glPopMatrix();
*/
}

std::string Objeto::set_nome(Vetor3D posicao, string nome){
    std::stringstream str;
    str << nome << " (" << posicao.x << "," << posicao.y << "," << posicao.z << ")";

    return str.str();


}



