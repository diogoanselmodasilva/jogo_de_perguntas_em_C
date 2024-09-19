#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>//para usar setlocale

#define MAX_PERGUNTAS 16
#define MAX_ALTERNATIVAS 4
#define MAX_TAM 256

char enunciado[MAX_PERGUNTAS][MAX_TAM];
char alternativas[MAX_PERGUNTAS][MAX_ALTERNATIVAS][MAX_TAM];
char resp_correta[MAX_PERGUNTAS];
int total_perguntas = 0;

//função para limpar o buffer para windows e linux
void limpar_buffer(){
    #ifdef _WIN32
        fflush(stdin);
    #else
        __fpurge(stdin);
    #endif
};
//Para limpar a tela para windows e linux
void limpar_tela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
};

void ler_perguntas(const char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", nome_arquivo);
        return;
    }

    while (fgets(enunciado[total_perguntas], MAX_TAM, file) != NULL) {
        // Remove a nova linha do final
        enunciado[total_perguntas][strcspn(enunciado[total_perguntas], "\n")] = 0;

        // Divide a linha em partes usando ';' como delimitador
        char *token = strtok(enunciado[total_perguntas], ";");
        int index = 0;

        // Captura a pergunta e as alternativas
        while (token != NULL) {
            if (index == 0) {
                // Primeira parte é o enunciado
                strcpy(enunciado[total_perguntas], token);
            } else if (index <= MAX_ALTERNATIVAS) {
                // Alternativas
                strcpy(alternativas[total_perguntas][index - 1], token);
            } else {
                // Resposta correta
                resp_correta[total_perguntas] = token[0]; // Pega o primeiro caractere
            }
            token = strtok(NULL, ";");
            index++;
        }
        total_perguntas++;
    }

    fclose(file);
}

void perguntas_facil() {
    total_perguntas = 0; // Resetar contador
    ler_perguntas("question_easy.txt");
}

void perguntas_medio() {
    total_perguntas = 0; // Resetar contador
    ler_perguntas("question_medium.txt");
}

void perguntas_dificil() {
    total_perguntas = 0; // Resetar contador
    ler_perguntas("question_hard.txt");
}

void jogar(int dificuldade) {
    char resp;
    for (int i = 0; i < 10; i++) {
        printf("\nPergunta %d: %s\n", i + 1, enunciado[i]);
        for (int j = 0; j < MAX_ALTERNATIVAS; j++) {
            printf(" %c) %s\n", 'a' + j, alternativas[i][j]);
        }
        printf("Digite sua resposta\n");
        resp = getchar();

        if (resp == resp_correta[i]) {
            printf("Certa resposta!\n");
        } else {
            printf("Resposta errada! A resposta correta era: %c\n", resp_correta[i]);
        }
        getchar();
        limpar_buffer();
    }
}


int main() {
    setlocale(LC_ALL, "Portuguese");
    int dificuldade;

    do {
        printf("\n------Bem vindo ao jogo!!!-----\n");
        printf("\n------Digite ENTER para continuar------\n");
        getchar();
        limpar_buffer();
        limpar_tela();
        printf("\n----- Escolha a dificuldade -----\n");
        printf("1 - Fácil\n");
        printf("2 - Médio\n");
        printf("3 - Difícil\n");
        scanf("%d", &dificuldade);
        getchar();
        limpar_buffer();

        switch (dificuldade) {
            case 1:
                perguntas_facil();
                jogar(dificuldade);
                break;
            case 2:
                perguntas_medio();
                jogar(dificuldade);
                break;
            case 3:
                perguntas_dificil();
                jogar(dificuldade);
                break;
            default:
                printf("Por favor, escolha um nível de dificuldade válido!\n");
                break;
        }
    } while (dificuldade != 0);

    return 0;
}
