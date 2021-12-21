#include <iostream>

using namespace std;

//#include <gui.h>
#include <vector>

//#include <objeto.h>
#include <personagem.h>
#include <casa.h>
#include <carro.h>
#include <lobo.h>

//Model3DS model3ds("../3ds/cartest.3DS");

vector<Objeto*> objetos;
int posSelecionado = -1;
//-------------------sombra-------------------
bool drawShadow = false;
bool pontual = true;
float k = 0.0;
//-------------------sombra-------------------

bool luzesEscondidas = true;
void desenha() {
    GUI::displayInit();

    GUI::setLight(4,1,3,5,true,false,false,luzesEscondidas);
    GUI::setLight(5,-1.5,0.5,-1,true,false,false,luzesEscondidas);
    GUI::setLight(6,-5,3,5,true,false,false,luzesEscondidas);

    GUI::drawOrigin(0.5);

    //GUI::setColor(1,0,0);
    GUI::setColor(0.6,0.4,0.0);
    glPushMatrix();
        //-------------------sombra-------------------
        glTranslated(0.0,k,0.0); //glTranslated(0.0,k-0.001,0.0);
        GUI::drawFloor(25,25); //-0.001 definido dentro do drawFloor

        //GUI::drawPlane(Vetor3D(2,2,3), k, 15, 15, 0.5, 0.5); //chama o drawFloor dentro //-0.001 definido dentro do drawFloor
        //GUI::drawPlane(Vetor3D(0,0,1), k, 15, 15, 0.5, 0.5);
        //GUI::drawPlane(Vetor3D(0,1,0), k, 15, 15, 0.5, 0.5);
        //-------------------sombra-------------------
    glPopMatrix();

    for (int i = 0; i < objetos.size(); ++i) {
        glPushMatrix();
            objetos[i]->desenha();
        glPopMatrix();
    }

    //-------------------sombra-------------------
    //definindo a luz que sera usada para gerar a sombra
    float lightPos[4] = {1.5+glutGUI::lx,1.5+glutGUI::ly,1.5+glutGUI::lz,pontual};
    //GUI::setLight(0,lightPos[0],lightPos[1],lightPos[2],true,false,false,false,pontual);
    GUI::setLight(0,1.5,1.5,1.5,true,false,false,false,pontual);
    //desenhando os objetos projetados
    glPushMatrix();
        //matriz p multiplicar tudo por -1
            //float neg[16] = {
            //                   -1.0, 0.0, 0.0, 0.0,
            //                    0.0,-1.0, 0.0, 0.0,
            //                    0.0, 0.0,-1.0, 0.0,
            //                    0.0, 0.0, 0.0,-1.0
            //                };
            //glMultTransposeMatrixf( neg );
        //matriz de projecao para gerar sombra no plano y=k
            GLfloat sombra[4][4];
            GUI::shadowMatrixYk(sombra,lightPos,k);
            //GLfloat plano[4] = {0,1,0,-k};
            //GUI::shadowMatrix(sombra,plano,lightPos);
            glMultTransposeMatrixf( (GLfloat*)sombra );

        //matriz de projecao para gerar sombra no plano y=k
            //GLfloat sombra[4][4];
            //GUI::shadowMatrixYk(sombra,lightPos,k);
            //GLfloat plano[4] = {0,1,0,-k};
            //GLfloat plano[4] = {0,0,1,-k};
            //GLfloat plano[4] = {1,1,0,-k};
            //GLfloat plano[4] = {sqrt(2)/2.,sqrt(2)/2.,0,-k}; //      2/4 + 2/4 + 0 = 1
            //versao plano arbitrario passando coeficiente D do plano (não intuitivo p usuario - diferente de acordo com o tamanho do n)
            //GLfloat plano[4] = {2,2,3,-k}; //D = -k
            //GUI::shadowMatrix(sombra,plano,lightPos);
            //versao plano arbitrario passando dist minima do plano para a origem (mais intuitivo p usuario)
            //GLfloat distMin = k; //sinal indica se a distancia é no sentido da normal ou contrário
            //GUI::shadowMatrix(sombra, Vetor3D(2,2,3), distMin, lightPos);
            //glMultTransposeMatrixf( (GLfloat*)sombra );



        glDisable(GL_LIGHTING);
        glColor3d(0.0,0.0,0.0);
        if (drawShadow) {
            bool aux = glutGUI::draw_eixos;
            glutGUI::draw_eixos = false;
            for (int i = 0; i < objetos.size(); ++i) {
                glPushMatrix();
                    objetos[i]->desenha();
                glPopMatrix();
            }
            glutGUI::draw_eixos = aux;
        }
        glEnable(GL_LIGHTING);
        //glDisable(GL_LIGHTING);
        //glColor3d(0.0,0.0,0.0);
        //if (drawShadow) desenhaObjetosComSombra();
        //glEnable(GL_LIGHTING);
    glPopMatrix();
    //-------------------sombra-------------------

    if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
        objetos[posSelecionado]->t.x += glutGUI::dtx;
        objetos[posSelecionado]->t.y += glutGUI::dty;
        objetos[posSelecionado]->t.z += glutGUI::dtz;

        objetos[posSelecionado]->a.x += glutGUI::dax;
        objetos[posSelecionado]->a.y += glutGUI::day;
        objetos[posSelecionado]->a.z += glutGUI::daz;

        objetos[posSelecionado]->s.x += glutGUI::dsx;
        objetos[posSelecionado]->s.y += glutGUI::dsy;
        objetos[posSelecionado]->s.z += glutGUI::dsz;
    }
    //glutGUI::dtx = 0.0; glutGUI::dty = 0.0; glutGUI::dtz = 0.0;
    //glutGUI::dax = 0.0; glutGUI::day = 0.0; glutGUI::daz = 0.0;
    //glutGUI::dsx = 0.0; glutGUI::dsy = 0.0; glutGUI::dsz = 0.0;

    GUI::displayEnd();
}

//bool incluirObjeto = false;

void teclado(unsigned char key, int x, int y) {
    //if (!incluirObjeto) {
        GUI::keyInit(key,x,y);
    //}

    switch (key) {
    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;

    case 'n':
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = false;
        }
        if (!objetos.empty()) {
            posSelecionado++;
            posSelecionado = posSelecionado%objetos.size();
        }
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = true;
        }
        break;
    case 'b':
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = false;
        }
        posSelecionado--;
        if (posSelecionado < 0) {
            posSelecionado = objetos.size()-1;
        }
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = true;
        }
        break;

    //case 'O':
    //    incluirObjeto = !incluirObjeto;
    //    break;
    case 'd':
        //if (incluirObjeto) {
            if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
                objetos.erase( objetos.begin() + posSelecionado );
            }
            posSelecionado = -1;
        //}
        break;
    //case 'p':
    //    if (incluirObjeto) {
    //        objetos.push_back( new Personagem() );
    //    }
    //    break;
    case '1':
    case 'M': //para compatibilizar com a implementacao da normalizacao da projecao (M: Modelo 3DS)
        //if (incluirObjeto) {
            objetos.push_back( new Lobo() );
        //}
        break;
    case '2':
        //if (incluirObjeto) {
            objetos.push_back( new Carro() );
        //}
        break;

    //-------------------sombra-------------------
    case 's':
        drawShadow = !drawShadow;
        break;
    case 'p':
        pontual = !pontual;
        break;
    case 'K':
        k += 0.1;
        break;
    case 'k':
        k -= 0.1;
        break;
    //-------------------sombra-------------------

    case 'L':
        luzesEscondidas = !luzesEscondidas;
        break;

    default:
        break;
    }
}

int main()
{
    cout << "Hello World!" << endl;

    GUI gui = GUI(800,600,desenha,teclado);
}


//while(true) {
//    desenha();
//    interacaoUsuario();
//}
