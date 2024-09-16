#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>//para usar setlocale

void main()
{
     // Configura o locale para permitir acentua��o
    setlocale(LC_ALL, "Portuguese");

    // Criando as vari�veis
    char enunciado1[2][256] = {
        "Qual o maior planeta do sistema solar?",
        "Quantos planetas tem o sistema solar?"
    };//O enunciado das perguntas
    char alternativas1[2][4][256] = {
        {"Terra", "Marte", "Jupiter", "Lua"},
        {"3", "8", "9", "6"}
    };//as alternativas das perguntas em ordem
    char resp_correta1[] = {'c', 'b'};//contem a alternativa correta de cada pergunta
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
    char resp_correta2[] = {'b','b'};
    int dificuldade;

    printf("\nBem-vindo ao jogo\n");
    printf("\n----- Jogar -----\n");

    for (i = 0; i < 2; i++) {
        printf("\nPergunta %d: %s\n", i + 1, enunciado1[i]);//imprimi o enunciado das perguntas
        for (j = 0; j < 4; j++) {
            printf(" %c) %s\n", 'a' + j, alternativas1[i][j]);//imprimi as alternativas das perguntas
        }
        resp = getchar();
        fflush(stdin);
        //verifica a resposta do jogador
        if(resp == resp_correta1[i]){
            printf("Certa resposta!");
        }
            else{
                printf("Resposta errada!");
            }

    }

}
