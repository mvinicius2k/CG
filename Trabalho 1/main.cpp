#include <iostream>
#include "trab1/Plano.h"
#include "trab1/Caixa.h"
#include "trab1/Objeto.h"
#include "trab1/Cubo.h"
#include "trab1/Casa.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <stdlib.h>


using namespace std;

#include <gui.h>

float esferaX = -1;
float caixaX = 0;

float objtx = 0.0; //Mouse direito
float objty = 0.0;
float objtz = 0.0;
float objax = 0.0; //Mouse esquerdo
float objay = 0.0;
float objaz = 0.0;
float objex = 1.0; // Mouse meio
float objey = 1.0;
float objez = 1.0;

bool esfera = false;
bool caixa = false;

bool selecionandoCor = false;

std::vector<Objeto*> vetorObjetos;
std::vector<Objeto*>::iterator itSelecao;


int i_selecao;

//list<Objeto*> listaObjetos;
//list<Objeto*>::iterator itSelecao;

typedef enum {Delete = 127, BackSpace = 8} Tecla;



bool existeObjSelecionado(){
    return i_selecao != -1;
}

void extrairValor(string str, float *var){
    int pos = str.find("=") + 1;
    string valor = str.substr(pos, str.length());
    //cout << "Valor-> " << valor << "|" << endl;
    *var = stof(valor);
}

void extrairValor(string str, int *var){
    int pos = str.find("=") + 1;
    string valor = str.substr(pos, str.length());
    //cout << "Valor-> " << valor << "|" << endl;
    *var = stoi(valor);
}

void addObjeto(Objeto *objeto){
    //if(dynamic_cast<Plano*>(objeto) != nullptr){
    //listaObjetos->push_front(objeto);
    //listaObjetos.insert(listaObjetos.begin(), objeto);


    if(glutGUI::trans_obj == true){
        glutGUI::trans_obj = !glutGUI::trans_obj;
    }



    if(existeObjSelecionado())
        (*itSelecao)->selecionado = false;

    i_selecao = -1;
    vetorObjetos.insert(vetorObjetos.begin(), objeto);
    cout << "Adicionando objeto " << vetorObjetos.size() << endl;

}



void carregar(){


    Objeto* obj;
    ifstream entrada;
    string linha;
    int estado = 0;
    int tipo;

    entrada.open("salvamento.cg");
    int i = 0;
    if(entrada.is_open()){

        float r,g,b,a,objax,objay,objaz,objex,objey,objez,objtx,objty,objtz;
        int especular, eixoLocal;
        float tamanho_x, tamanho_z, tamanho;

        while (getline(entrada, linha)) {



            stringstream comp[3];
            comp[0] << Objeto::PlanoObj << "{";
            comp[1] << Objeto::CuboObj << "{";
            comp[2] << Objeto::CasaObj << "{";

            if(estado == 0){
                if(linha == comp[0].str()){
                    obj = new Plano();
                    tipo = Objeto::PlanoObj;
                } else if(linha == comp[1].str()){
                    obj = new Cubo();
                    tipo = Objeto::CuboObj;
                } else if(linha == comp[2].str()){
                    obj = new Casa();
                    tipo = Objeto::CasaObj;
                  //
                } else {
                    cout << "wtf" << endl;
                }


                estado = 1;


            }


            if(estado == 1){
                if(linha.find("r=") == 0)
                    extrairValor(linha, &r);
                if(linha.find("g=") == 0)
                    extrairValor(linha, &g);
                if(linha.find("b=") == 0)
                    extrairValor(linha, &b);
                if(linha.find("a=") == 0)
                    extrairValor(linha, &a);
                if(linha.find("especular=") == 0)
                    extrairValor(linha, &especular);
                if(linha.find("ax=") == 0)
                    extrairValor(linha, &objax);
                if(linha.find("ay=") == 0)
                    extrairValor(linha, &objay);
                if(linha.find("az=") == 0)
                    extrairValor(linha, &objaz);
                if(linha.find("ex=") == 0)
                    extrairValor(linha, &objex);
                if(linha.find("ey=") == 0)
                    extrairValor(linha, &objey);
                if(linha.find("ez=") == 0)
                    extrairValor(linha, &objez);
                if(linha.find("tx=") == 0)
                    extrairValor(linha, &objtx);
                if(linha.find("ty=") == 0)
                    extrairValor(linha, &objty);
                if(linha.find("tz=") == 0)
                    extrairValor(linha, &objtz);



                //Plano
                if(tipo == Objeto::PlanoObj){
                    if(linha.find("tamanho_x=") == 0)
                        extrairValor(linha, &tamanho_x);
                    if(linha.find("tamanho_z=") == 0)
                        extrairValor(linha, &tamanho_z);
                } else if(tipo == Objeto::CuboObj){
                    if(linha.find("tamanho=") == 0)
                        extrairValor(linha, &tamanho);
                }

                if(linha == "}"){
                    obj->setColor(r,g,b,a,especular);
                    obj->posicao = Vetor3D(0,0,0);
                    obj->objax = objax;
                    obj->objay = objay;
                    obj->objaz = objaz;
                    obj->objex = objex;
                    obj->objey = objey;
                    obj->objez = objez;
                    obj->objtx = objtx;
                    obj->objty = objty;
                    obj->objtz = objtz;
                    obj->eixoLocal = false;

                    if(tipo == Objeto::PlanoObj){
                        Plano *p = dynamic_cast<Plano*>(obj);
                        p->tamanho_x = tamanho_x;
                        p->tamanho_z = tamanho_z;
                    } else if(tipo == Objeto::CuboObj){
                        Cubo *c = dynamic_cast<Cubo*>(obj);
                        c->tamanho = tamanho;
                    }

                    addObjeto(obj);

                    estado = 0;
                }

            }


            //cout << i++ << ": " << linha << endl;
        }
        cout << "Carregado com sucesso" << endl;
        entrada.close();
    }

}

void salvar(){
    stringstream stringa;
    ofstream saida;




    vector<Objeto*>::iterator it;

    for(it = vetorObjetos.begin(); it != vetorObjetos.end(); it++){
        stringa << (*it)->tipo << "{\n";
        stringa << "r=" << (*it)->cor.r << "\n";
        stringa << "g=" << (*it)->cor.g << "\n";
        stringa << "b=" << (*it)->cor.b << "\n";
        stringa << "a=" << (*it)->cor.a << "\n";
        stringa << "especular=" << (*it)->cor.especular << "\n";

        stringa << "tx=" << (*it)->objtx << "\n";;
        stringa << "ty=" << (*it)->objty << "\n";;
        stringa << "tz=" << (*it)->objtz << "\n";;
        stringa << "ax=" << (*it)->objax << "\n";;
        stringa << "ay=" << (*it)->objay << "\n";;
        stringa << "az=" << (*it)->objaz << "\n";;
        stringa << "ex=" << (*it)->objex << "\n";;
        stringa << "ey=" << (*it)->objey << "\n";;
        stringa << "ez=" << (*it)->objez << "\n";;

        //stringa << "eixoLocal=" << (*it)->eixoLocal << "\n";

        if((*it)->tipo == Objeto::PlanoObj){
            Plano *p = dynamic_cast<Plano*>((*it));
            stringa << "tamanho_x=" << p->tamanho_x << "\n";
            stringa << "tamanho_z=" << p->tamanho_z << "\n";
        } else if((*it)->tipo == Objeto::CuboObj){
            Cubo *c = dynamic_cast<Cubo*>(*it);
            stringa << "tamanho=" << c->tamanho << "\n";
        } else if((*it)->tipo == Objeto::CasaObj){
            Casa *h = dynamic_cast<Casa*>(*it);
        }

        stringa << "}\n";



    }



    saida.open("./salvamento.cg");
    saida.flush();
    saida << stringa.str();

    cout << "Salvo com sucesso em /salvamento.cg";
    saida.close();



}





void initFormas(){
    i_selecao = -1;
    srand(time(0));

    //Plano *plano = new Plano(Vetor3D(0,0,0), 5, 3);
    //Cubo *cubo = new Cubo(Vetor3D(0,0,0), 3);

    //cubo->setColor(0.9,0,0);

    //addObjeto(plano);
    //addObjeto(cubo);

    //


    itSelecao = vetorObjetos.begin();

}

//Model3DS modelo3ds = Model3DS("../3ds/cartest.3DS");

void desenhaObjeto()
{
    glBegin(GL_POLYGON);

        glNormal3f(0,0,1);
        glVertex3f(1,0,0);
        glVertex3f(1,1,0);
        glVertex3f(0,1,0);
        glVertex3f(0,0,0);
    glEnd();
}

void desenha() {
    GUI::displayInit();

    //vetorObjetos[posSel].tx += glutGUI::dtx;
    /*
    objtx += glutGUI::dtx;
    objty += glutGUI::dty;
    objtz += glutGUI::dtz;
    objax += glutGUI::dax;
    objay += glutGUI::day;
    objaz += glutGUI::daz;
    objex += glutGUI::dsx;
    objey += glutGUI::dsy;
    objez += glutGUI::dsz;

*/





    GUI::setLight(0, 0,2,0, true, false);

    //referencia (sistema de coordenadas global)

    GUI::setColor(1,1,1);
    GUI::drawFloor(50,50,20);

    GUI::setColor(0,1,0, 0.5);


    //GUI::setColor(0,0,1);
    //GUI::drawBox(-5,-5,-2, 5,5,2, true);

    GUI::setColor(0,0,1);


    std::vector<Objeto*>::iterator it;
    int h = 0;


    //for( cada objeto ) {

        for(it = vetorObjetos.begin(); it != vetorObjetos.end(); it++){
                objtx = (*it)->objtx;
                objax = (*it)->objax;
                objex = (*it)->objex;

                objty = (*it)->objty;
                objay = (*it)->objay;
                objey = (*it)->objey;

                objtz = (*it)->objtz;
                objaz = (*it)->objaz;
                objez = (*it)->objez;

            glPushMatrix();
                /*glTranslatef(objtx,objty,objtz); //Translação
                glRotatef(objax,1,0,0); //Rotação
                glRotatef(objay,0,1,0); //Rotação
                glRotatef(objaz,0,0,1); //Rotação
                glScalef(objex,objey,objez); //Escala
                */

                glTranslatef(objtx,objty,objtz); //Translação
                glRotatef(objax,1,0,0); //Rotação
                glRotatef(objay,0,1,0); //Rotação
                glRotatef(objaz,0,0,1); //Rotação
                glScalef(objex,objey,objez); //Escala

               // GUI::drawOrigin(0.5); //Setas
                //desenhaObjeto(); //Objeto a se aplicar as transformações

                (*it)->desenhar();


            glPopMatrix();

        }
        /*

*/

    //}
/*
    glPushMatrix();
        glTranslatef(2,1,-1);
        GUI::setColor(0,0,1);
        //GUI::draw3ds(modelo3ds,-1,0,1);
    glPopMatrix();
*/
    GUI::displayEnd();
}


void selecionarProxObj(bool reverso = false)
{
    if(existeObjSelecionado())
        (*itSelecao)->selecionado = false;

    if(reverso == false){
        if(i_selecao == vetorObjetos.size()-1 || i_selecao == -1){
            itSelecao = vetorObjetos.begin();
            i_selecao = 0;
            (*itSelecao)->selecionado = true;
            return;
        }

        itSelecao++;
        i_selecao++;
    } else {
        if(i_selecao == 0 || i_selecao == -1){
            itSelecao = vetorObjetos.end();
            itSelecao--;
            i_selecao = vetorObjetos.size()-1;
            (*itSelecao)->selecionado = true;
            return;
        }

        itSelecao--;
        i_selecao--;
    }

    (*itSelecao)->selecionado = true;
}



void removerObjeto(vector<Objeto*>::iterator &it){

}

void teclado(unsigned char tecla, int x, int y) {
    GUI::keyInit(tecla,x,y);




    switch (tecla) {
    case 'L':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;
    case 'T':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        break;

    case 'W':
        if(vetorObjetos.size() != 0)
            selecionarProxObj();
        break;
    case 'S':
        if(vetorObjetos.size() != 0)
            selecionarProxObj(true);
        break;
    case '\'':
        if(existeObjSelecionado())
            (*itSelecao)->selecionado = false;
        break;
    case 'K':
        if(existeObjSelecionado()){
            float c1 = (rand() % 100),
                  c2 = (rand() % 100),
                  c3 = (rand() % 100);
            (*itSelecao)->setColor(c1/100, c2/100, c3/100);
        }


        break;
    case 'E':
        if(existeObjSelecionado()){
            (*itSelecao)->eixoLocal = !(*itSelecao)->eixoLocal;
        }
        break;
    case Delete:
        if(existeObjSelecionado()){
            (*itSelecao)->selecionado = false;
            vetorObjetos.erase(itSelecao);
            i_selecao = -1;

        }
        break;
    case BackSpace:
        cout << "Backspace";
        if(!vetorObjetos.empty()){
            if(existeObjSelecionado())
                (*itSelecao)->selecionado = false;

            vetorObjetos.erase(vetorObjetos.begin());
            i_selecao = -1;

        }
        break;
    case 'O':
        salvar();
        break;
    case 'I':
        carregar();
        break;
    case '1':

        addObjeto(new Plano(Vetor3D(0,0,0),2,2));

        break;
    case '2':
        addObjeto(new Cubo(Vetor3D(0,0,0),2));
        break;
    case '3':
        addObjeto(new Casa());
        break;
    case 'R':
        if(!vetorObjetos.empty()){
            if(existeObjSelecionado())
                (*itSelecao)->cor.r = (fmod((*itSelecao)->cor.r + 5, 100))/100;


        }
        break;
    case 'G':
        if(!vetorObjetos.empty()){
            if(existeObjSelecionado())
                (*itSelecao)->cor.g = (fmod((*itSelecao)->cor.g + 5, 100))/100;


        }
        break;
    case 'B':
        if(!vetorObjetos.empty()){
            if(existeObjSelecionado())
                (*itSelecao)->cor.b = (fmod((*itSelecao)->cor.b + 5, 100))/100;


        }
        break;

    default:
        break;
    }
}





int main()
{
    cout << "Hello World!" << endl;
    initFormas();

    GUI gui = GUI(800,600,desenha,teclado);
}

//inicializando OpenGL
//while(true) {
//    desenha();
//    interacaoUsuario();
//}
