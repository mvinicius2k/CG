## Instala��o 
O trabalho foi feito usando o Visual Studio (v 2022). Deve ser poss�vel usar tamb�m no vscode, qt, cmake, vim, nano, notepad etc sem alterar o c�digo, mas algumas configura��es no vinculador e nos par�metros de compila��o precisar�o ser feitas uma vez que o trabalho foi feito no visual studio. Configura��o de Diret�rios e Entrada (dentro de Vinculador) foram algumas das altera��es que foram feitas para fazer o projeto do Qt Linux funcionar corretamente no Windows com Visual Studio.

0. Tenha o Visual Studio com o m�dulo de 'Desenvolvimento de jogos em C++' (n�o � necess�rio baixar o suporte para Unreal), ou o m�dulo 'Desenvolvimento para Desktop com C++', tanto faz. 
1. Clone o reposit�rio
2. Abra a pasta /CG/dll, copie todas as dlls e cole nas pastas C:/Windows/System32 e C:/Windows/SysWOW64
3. Abra o projeto sln
4. Mude a plataforma de solu��o de x64 para x86 (as libs s�o x86)
5. Pronto

