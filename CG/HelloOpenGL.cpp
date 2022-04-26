// HelloOpenGL.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <windows.h>
#include <iostream>
//#include <GL/glew.h>
#include <glut.h>

void desenhaMinhaCena(void)
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 1, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
    glEnd();
    glFlush();
}

//int main(int argc, char** argv)
//{
//    argc = 0;
//    argv = nullptr;
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE);
//    glutInitWindowSize(500, 500);
//    glutCreateWindow("Hello World");
//    glutDisplayFunc(desenhaMinhaCena);
//    glutMainLoop();
//    return 0;
//}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
