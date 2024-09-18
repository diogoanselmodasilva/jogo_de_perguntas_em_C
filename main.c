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
//perguntas dificil
char enunciado3[2][256] = {
    "Qual � a principal raz�o pela qual Plut�o n�o � mais considerado um planeta do Sistema Solar?",
    "O que afirma o princ�pio da incerteza de Heisenberg?"
};
char alternativas3[2][4][256] = {
    {"Sua �rbita � inclinada em rela��o ao plano do Sistema Solar.", "N�o � grande o suficiente para limpar sua �rbita de outros objetos.", "Ele n�o possui sat�lites naturais.", "Sua composi��o � predominantemente gasosa."}
    {"N�o � poss�vel medir simultaneamente a posi��o e a velocidade de uma part�cula com precis�o arbitr�ria.","A energia total de um sistema isolado � sempre constante.","A luz pode se comportar como part�cula e como onda.","A gravidade � a for�a mais fraca entre as quatro for�as fundamentais."}
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


};
//fun��o para perguntas medio
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
    // Configura o locale para permitir acentua��o
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
    printf("\n1- F�cil\n");
    printf("\n2- M�dio\n");
    scanf("%d",&dificuldade);
    __fpurge(stdin);

    switch(dificuldade){
        case 1: perguntas_facil();
        break;
        case 2: perguntas_medio();
        break;
        default: printf("Por favor escolha um n�vel de dificuldade!");
        }
}

