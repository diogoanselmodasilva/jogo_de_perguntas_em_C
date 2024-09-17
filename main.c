#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>//para usar setlocale


// Criando as vari�veis
char enunciado1[2][256] = {
    "Qual o maior planeta do sistema solar?",
    "Quantos planetas tem o sistema solar?"
};//O enunciado das perguntas
char alternativas1[2][4][256] = {
    {"Terra", "Marte", "Jupiter", "Lua"},
    {"3", "8", "9", "6"}
};//as alternativas das perguntas em ordem
char resp_correta1[] = {'c', 'b'};//contem a alternativa correta de cada pergunta facil
//perguntas de dificuldade media
char enunciado2[2][256] = {
    "O que afirma a lei de Coloumb?",
    "Qual � a unidade de medida de for�a no sistema internacional?"
};
//alternativas de dificuldade media
char alternativas2[2][4][256] = {
    {" A for�a de atrito � diretamente proporcional � for�a normal", " A for�a el�trica entre duas cargas � inversamente proporcional ao quadrado da dist�ncia entre elas"," A energia cin�tica � a mesma que a energia potencial"," A velocidade de um objeto � constante se a for�a resultante for zero"},
    {"Joule","Newton","Pascal","Watt"}
};
int i, j;
char resp;
char resp_correta2[] = {'b','b'};//resposta correta das dificuldades nivel medio
int dificuldade;

//fun��o para perguntas faceis
char perguntas_facil(){
      for (i = 0; i < 2; i++) {
        printf("\nPergunta %d: %s\n", i + 1, enunciado1[i]);//imprimi o enunciado das perguntas
            for (j = 0; j < 4; j++) {
                printf(" %c) %s\n", 'a' + j, alternativas1[i][j]);//imprimi as alternativas das perguntas
            }
            resp = getchar();
            #ifdef _WIN32
                system("ffslush(stdin");//para windows
            Windows
            #else
                __fpurge(stdin);//para linux e macos
             #endif
            //verifica a resposta do jogador
            if(resp == resp_correta1[i]){
                printf("Certa resposta!");
                }
                else{
                    printf("Resposta errada!");
            }
    }
}
//variavel pra receber a fun��o

void main(){
    // Configura o locale para permitir acentua��o
    setlocale(LC_ALL, "Portuguese");

    printf("\n-----Bem-vindo ao jogo-----\n");
    printf("\n-----Pressione enter para continuar -----\n");
    getchar();
    //limpar a tela
    #ifdef _WIN32
        system("cls"); //comando para windows
    Windows
    #else
        system("clear");//comano para Linux e MacOs
    #endif

    printf("Escolha a dificuldade:");
    printf("\n1- F�cil\n");
    printf("\n2- M�dio\n");
    dificuldade = getchar();
    __fpurge(stdin);
    switch(dificuldade){
        case 1: perguntas_facil();
        break;
    }
}

