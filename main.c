#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>//para usar setlocale


// Criando as variáveis
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
    "Qual é a unidade de medida de força no sistema internacional?"
};
//perguntas dificil
char enunciado3[2][256] = {
    "Qual é a principal razão pela qual Plutão não é mais considerado um planeta do Sistema Solar?",
    "O que afirma o princípio da incerteza de Heisenberg?"
};
char alternativas3[2][4][256] = {
    {"Sua órbita é inclinada em relação ao plano do Sistema Solar.", "Não é grande o suficiente para limpar sua órbita de outros objetos.", "Ele não possui satélites naturais.", "Sua composição é predominantemente gasosa."}
    {"Não é possível medir simultaneamente a posição e a velocidade de uma partícula com precisão arbitrária.","A energia total de um sistema isolado é sempre constante.","A luz pode se comportar como partícula e como onda.","A gravidade é a força mais fraca entre as quatro forças fundamentais."}
};
//alternativas de dificuldade media
char alternativas2[2][4][256] = {
    {" A força de atrito é diretamente proporcional à força normal", " A força elétrica entre duas cargas é inversamente proporcional ao quadrado da distância entre elas"," A energia cinética é a mesma que a energia potencial"," A velocidade de um objeto é constante se a força resultante for zero"},
    {"Joule","Newton","Pascal","Watt"}
};
int i, j;
char resp;
char resp_correta2[] = {'b','b'};//resposta correta das dificuldades nivel medio
int dificuldade;
//função para perguntas faceis
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


};
//função para perguntas medio
char perguntas_medio(){
     for (i = 0; i < 2; i++) {
        printf("\nPergunta %d: %s\n", i + 1, enunciado2[i]);//imprimi o enunciado das perguntas
            for (j = 0; j < 4; j++) {
                printf(" %c) %s\n", 'a' + j, alternativas2[i][j]);//imprimi as alternativas das perguntas
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

void main(){
    // Configura o locale para permitir acentuação
    setlocale(LC_ALL, "Portuguese");

    printf("\n-----Bem-vindo ao jogo-----\n");
    printf("\n-----Pressione enter para continuar -----\n");
    getchar();
    #ifdef _WIN32
            system("ffslush(stdin");//para windows
        Windows
        #else
            __fpurge(stdin);//para linux e macos
    #endif
    //verifica a resposta do jogador
    //limpar a tela
    #ifdef _WIN32
        system("cls"); //comando para windows
    Windows
    #else
        system("clear");//comano para Linux e MacOs
    #endif

    printf("Escolha a dificuldade:");
    printf("\n1- Fácil\n");
    printf("\n2- Médio\n");
    scanf("%d",&dificuldade);
    __fpurge(stdin);

    switch(dificuldade){
        case 1: perguntas_facil();
        break;
        case 2: perguntas_medio();
        break;
        default: printf("Por favor escolha um nível de dificuldade!");
        }
}

