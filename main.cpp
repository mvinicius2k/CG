#include <iostream>
#include <gui.h>



using namespace std;


//Model3DS carro = Model3DS("../3ds/cartest.3DS");

void modeloTeste()
{
    //face traseira
    //glDisable(GL_CULL_FACE);
    glPushMatrix();
        //static float rot = 0;
        //rot += 0.2;
        //glRotatef(rot, 1,1,0);
        glRotatef(180, 1,1,0);
        glBegin( GL_POLYGON );
            glNormal3f( 0,0,1 );
            glVertex3f( 0,0,0 );
            glVertex3f( 1,0,0 );
            glVertex3f( 1,1,0 );
            glVertex3f( 0,1,0 );
        glEnd();
    glPopMatrix();
    //glEnable(GL_CULL_FACE);

    //face inferior
    glPushMatrix();
        glRotatef(180, 1,0,1);
        glBegin( GL_POLYGON );
            glNormal3f( 0,1,0 );
            glVertex3f( 0,0,0 );
            glVertex3f( 0,0,1 );
            glVertex3f( 1,0,1 );
            glVertex3f( 1,0,0 );
        glEnd();
    glPopMatrix();

    //face esquerda
    glPushMatrix();
        glRotatef(90, 0,0,1);
        glBegin( GL_POLYGON );
            glNormal3f( 0,1,0 );
            glVertex3f( 0,0,0 );
            glVertex3f( 0,0,1 );
            glVertex3f( 1,0,1 );
            glVertex3f( 1,0,0 );
        glEnd();
    glPopMatrix();

    //face frontal
    glPushMatrix();
        glTranslatef(0,0,1);
        glBegin( GL_POLYGON );
            glNormal3f( 0,0,1 );
            glVertex3f( 0,0,0 );
            glVertex3f( 1,0,0 );
            glVertex3f( 1,1,0 );
            glVertex3f( 0,1,0 );
        glEnd();
    glPopMatrix();

    //face direita
    glPushMatrix();
        //testamos diferentes composições de transformações
        glTranslatef(1,0,0);
        glTranslatef(0,0,1);
        glRotatef(90, 0,1,0);
        //GUI::drawOrigin(0.5);
        glBegin( GL_POLYGON );
            glNormal3f( 0,0,1 );
            glVertex3f( 0,0,0 );
            glVertex3f( 1,0,0 );
            glVertex3f( 1,1,0 );
            glVertex3f( 0,1,0 );
        glEnd();
    glPopMatrix();

    //face superior
    glPushMatrix();
        glRotatef(-90, 1,0,0);
        glTranslatef(0,-1,1);
        //GUI::drawOrigin(0.5);
        glBegin( GL_POLYGON );
            glNormal3f( 0,0,1 );
            glVertex3f( 0,0,0 );
            glVertex3f( 1,0,0 );
            glVertex3f( 1,1,0 );
            glVertex3f( 0,1,0 );
        glEnd();
    glPopMatrix();


    //face telhado esquerdo
    glPushMatrix();
        glRotatef(-90, 1,0,0);
        glTranslatef(0,-1,1);
        glRotatef(45, 0,-1,0);
        glTranslatef(-0.29,0,0);
        //GUI::drawOrigin(0.5);
        glBegin( GL_POLYGON );
            glNormal3f( 0,0,1 );
            glVertex3f( 0,0,0 );
            glVertex3f( 1,0,0 );
            glVertex3f( 1,1,0 );
            glVertex3f( 0,1,0 );
        glEnd();
    glPopMatrix();

    //face telhado direito
    glPushMatrix();
        glRotatef(-90, 1,0,0);
        glTranslatef(0,-1,1);
        glTranslatef(1,0,0);
        glRotatef(-45, 0,-1,0);
        glTranslatef(-0.71,0,0);
        //GUI::drawOrigin(0.5);
        glBegin( GL_POLYGON );
            glNormal3f( 0,0,1 );
            glVertex3f( 0,0,0 );
            glVertex3f( 1,0,0 );
            glVertex3f( 1,1,0 );
            glVertex3f( 0,1,0 );
        glEnd();
    glPopMatrix();

    //    //face inclinada
    //    glBegin( GL_POLYGON );
    //        glNormal3f( 1,1,0 );
    //        glVertex3f( 0,1,0 );
    //        glVertex3f( 0,1,1 );
    //        glVertex3f( 1,0,1 );
    //        glVertex3f( 1,0,0 );
    //    glEnd();
    //    glTranslatef( 0,1,0 );
    //    glRotatef( -45, 0,0,1 );
    //    glBegin( GL_POLYGON );
    //        glNormal3f( 0,1,0 );
    //        glVertex3f( 0,0,0 );
    //        glVertex3f( 0,0,1 );
    //        glVertex3f( 1,0,1 );
    //        glVertex3f( 1,0,0 );
    //    glEnd();
}


float esferaPosX = 0;
float esferaPosY = 0;
float esferaRotZ = 0;
float esferaEscX = 1;
float esferaEscY = 1;

float caixaPosX = 0;
float caixaPosY = 0;
float caixaPosZ = 0;
float caixaRotX = 0;
float caixaRotY = 0;
float caixaRotZ = 0;
float caixaEscX = 1;
float caixaEscY = 1;
float caixaEscZ = 1;

bool caixa = true;

/**
 * Draw a character string.
 *
 * @param x        The x position
 * @param y        The y position
 * @param z        The z position
 * @param string   The character string
 */
void drawString(float x, float y, float z, char *string) {
  glRasterPos3f(x, y, z);

  for (char* c = string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);  // Updates the position
  }
}

void desenha() {
    GUI::displayInit();

    //GUI::setLight(0,  0,1,0, true); //,false);
    //GUI::setLight(1,  1,1,0, true); //,false);
    //GUI::setLight(2, -1,1,0, true); //,false);
    //GUI::setLight(3,  0,0.5,0, true); //,false);

drawString(0.,0.,0., "Teste");
string str_obj("Texto para UI");



glMatrixMode( GL_PROJECTION );
glPushMatrix();
glLoadIdentity();
gluOrtho2D( 0, 1280, 0, 1024 );

glMatrixMode( GL_MODELVIEW );
glPushMatrix();
glLoadIdentity();
glRasterPos2i( 10, 1014 );  // move in 10 pixels from the left and bottom edges
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, '1');

glPopMatrix();

glMatrixMode( GL_PROJECTION );
glPopMatrix();
glMatrixMode( GL_MODELVIEW );

    GUI::setLight(0,  3,5,4, true,false);

    GUI::drawOrigin(0.5);
    GUI::setColor(1,0,0, 1,true);
    //GUI::drawFloor(5,5,0.1,0.1);
    GUI::drawFloor();


    if (caixa) {
        //olhar a funcao mouseMove no arquivo extra (class glutGUI)
        caixaPosX += glutGUI::dtx; //configuracao da movimentacao do mouse: bDir, horiz, devagar
        caixaPosY += glutGUI::dty; //configuracao da movimentacao do mouse: bDir,  vert, devagar
        caixaPosZ += glutGUI::dtz; //configuracao da movimentacao do mouse: bD+E,  vert, devagar
        caixaRotX += glutGUI::dax; //configuracao da movimentacao do mouse: bEsq,  vert, rapido
        caixaRotY += glutGUI::day; //configuracao da movimentacao do mouse: bEsq, horiz, rapido
        caixaRotZ += glutGUI::daz; //configuracao da movimentacao do mouse: bD+E, horiz, rapido
        caixaEscX += glutGUI::dsx; //configuracao da movimentacao do mouse: bMei, horiz, ?
        caixaEscY += glutGUI::dsy; //configuracao da movimentacao do mouse: bMei,  vert, ?
        caixaEscZ += glutGUI::dsz; //configuracao da movimentacao do mouse: bE+M,  vert, ?
    } else {
        esferaPosX += glutGUI::dtx;
        esferaPosY += glutGUI::dty;
        esferaRotZ += glutGUI::daz;
        esferaEscX += glutGUI::dsx;
        esferaEscY += glutGUI::dsy;
    }


    //vert_saida = Mt . Mr . Me . vert_entrada

    //vert_saida = I . T . vert_entrada
    //vert_saida = T . R . vert_entrada
    //vert_saida = R . vert_tarnsladado

    glPushMatrix();
        //interpretacao:
        //                 -----> local
        //                 <----- global
        //vert_saida = I . T . R . vert_entrada
        glTranslatef( caixaPosX, caixaPosY, caixaPosZ );
        glRotatef( caixaRotX, 1,0,0 );
        glRotatef( caixaRotY, 0,1,0 );
        glRotatef( caixaRotZ, 0,0,1 );
        glScalef( caixaEscX, caixaEscY, caixaEscZ );
        //GUI::glShearXZf( caixaPosX, caixaPosZ );
        //GUI::glShearYZf( caixaPosY, caixaPosZ );
        //GUI::glShearXYf( caixaPosX, caixaPosY );
        //GUI::glShearXf( caixaPosY, caixaPosZ );
        //caixa
        GUI::drawOrigin(0.5);
        GUI::setColor(1,1,1, 1,true);
        //modeloTeste();
        //desfazendo as tranformações locais do 3ds
        glScalef(1,1,1);
        glRotatef(-90, 1,0,0);
        glTranslatef(0,0,0);
        glScalef(0.0005,0.0005,0.0005);
        //carro.draw( false );
    glPopMatrix();

//    glPushMatrix();
//        glTranslatef( esferaPosX, esferaPosY, 0 );
//        glRotatef( esferaRotZ, 0,0,1 );
//        glScalef( esferaEscX, esferaEscY, 1 );
//        //caixa
//        GUI::drawOrigin(0.5);
//        GUI::setColor(0,1,0, 1,true);
//        GUI::drawSphere(0,0,0, 0.2);
//    glPopMatrix();

    GUI::displayEnd();
}

void teclado( unsigned char tecla, int mouseX, int mouseY ) {
    GUI::keyInit(tecla,mouseX,mouseY);

    switch (tecla) {
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;
    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        break;
    case 's':
        caixa = !caixa;
        break;

    //case 'w':
    //    esferaPosY += 0.2;
    //    break;
    //case 's':
    //    esferaPosY -= 0.2;
    //    break;
    //case 'a':
    //    esferaPosX -= 0.2;
    //    break;
    //case 'd':
    //    esferaPosX += 0.2;
    //    break;
    //case 'r':
    //    esferaRaio *= 0.5;
    //    break;
    //case 'R':
    //    esferaRaio *= 2;
    //    break;
    default:
        break;
    }
}

int main()
{
    cout << "Hello World!" << endl;

    //GUI gui();
    GUI gui = GUI(800,600,desenha,teclado);
}

//inicializando OpenGL
//while(true) {
//    desenha();
//    interacaoUsuario();
//    //if () {
//    //    break;
//    //}
//}




//Espelhamento

//glPushMatrix();
//    //caixa
//    glTranslatef( caixaPosX, caixaPosY, caixaPosZ );
//    glRotatef( caixaRotX, 1,0,0 );
//    glRotatef( caixaRotY, 0,1,0 );
//    glRotatef( caixaRotZ, 0,0,1 );
//    glScalef( caixaEscX, caixaEscY, caixaEscZ );
//    GUI::drawOrigin(0.5);
//    GUI::setColor(0,0,1, 1,true);
//    modeloTeste();
//glPopMatrix();
//glDisable(GL_CULL_FACE);
//glPushMatrix();
//    GUI::glReflectPlaneXYf();
//    //interpretacao:
//    //                 -----> local
//    //                 <----- global
//    //vert_saida = I . T . R . vert_entrada
//    glTranslatef( caixaPosX, caixaPosY, caixaPosZ );
//    glRotatef( caixaRotX, 1,0,0 );
//    glRotatef( caixaRotY, 0,1,0 );
//    glRotatef( caixaRotZ, 0,0,1 );
//    glScalef( caixaEscX, caixaEscY, caixaEscZ );
//    //GUI::glShearXZf( caixaPosX, caixaPosZ );
//    //GUI::glShearYZf( caixaPosY, caixaPosZ );
//    //GUI::glShearXYf( caixaPosX, caixaPosY );
//    //GUI::glShearXf( caixaPosY, caixaPosZ );
//    //caixa
//    GUI::drawOrigin(0.5);
//    GUI::setColor(0,0,1, 1,true);
//    modeloTeste();
//    //desfazendo as tranformações locais do 3ds
//    //glScalef(1,1,1);
//    //glRotatef(-90, 1,0,0);
//    //glTranslatef(0,0,0);
//    //glScalef(0.0005,0.0005,0.0005);
//    //carro.draw();
//glPopMatrix();
//glEnable(GL_CULL_FACE);
