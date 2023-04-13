## Instalação 
O trabalho foi feito usando o Visual Studio (v 2022). Deve ser possível usar também no vscode, qt, cmake, vim, nano, notepad etc sem alterar o código, mas algumas configurações no vinculador e nos parâmetros de compilação precisarão ser feitas uma vez que o trabalho foi feito no visual studio. Configuração de Diretórios e Entrada (dentro de Vinculador) foram algumas das alterações que foram feitas para fazer o projeto do Qt Linux funcionar corretamente no Windows com Visual Studio.

0. Tenha o Visual Studio com o módulo de 'Desenvolvimento de jogos em C++' (não é necessário baixar o suporte para Unreal), ou o módulo 'Desenvolvimento para Desktop com C++', tanto faz. 
1. Clone o repositório
2. Abra a pasta /CG/dll, copie todas as dlls e cole nas pastas C:/Windows/System32 e C:/Windows/SysWOW64
3. Abra o projeto sln
4. Mude a plataforma de solução de x64 para x86 (as libs são x86)
5. Pronto

