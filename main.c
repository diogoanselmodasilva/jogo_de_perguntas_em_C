#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define MAX_PERGUNTAS 16
#define MAX_ALTERNATIVAS 4
#define MAX_TAM 512

char enunciado[MAX_PERGUNTAS][MAX_TAM];
char alternativas[MAX_PERGUNTAS][MAX_ALTERNATIVAS][MAX_TAM];
char resp_correta[MAX_PERGUNTAS];
int total_perguntas = 0;

// Função para limpar o buffer
void limpar_buffer() {
    #ifdef _WIN32
        fflush(stdin);
    #else
        __fpurge(stdin);
    #endif
}

// Função para limpar a tela
void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função para embaralhar perguntas
void embaralhar_perguntas() {
    srand(time(NULL)); // Inicializa a semente aleatória
    for (int i = total_perguntas - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Embaralha o enunciado
        char temp_enunciado[MAX_TAM];
        strcpy(temp_enunciado, enunciado[i]);
        strcpy(enunciado[i], enunciado[j]);
        strcpy(enunciado[j], temp_enunciado);

        // Embaralha as alternativas
        for (int k = 0; k < MAX_ALTERNATIVAS; k++) {
            char temp_alternativa[MAX_TAM];
            strcpy(temp_alternativa, alternativas[i][k]);
            strcpy(alternativas[i][k], alternativas[j][k]);
            strcpy(alternativas[j][k], temp_alternativa);
        }

        // Embaralha as respostas corretas
        char temp_resp = resp_correta[i];
        resp_correta[i] = resp_correta[j];
        resp_correta[j] = temp_resp;
    }
}

void ler_perguntas(const char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", nome_arquivo);
        return;
    }

    total_perguntas = 0; // Resetar contador
    while (fgets(enunciado[total_perguntas], MAX_TAM, file) != NULL && total_perguntas < MAX_PERGUNTAS) {
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
            } else if (index == MAX_ALTERNATIVAS + 1) {
                // Resposta correta
                resp_correta[total_perguntas] = token[0]; // Pega o primeiro caractere
            }
            token = strtok(NULL, ";");
            index++;
        }
        total_perguntas++;
    }

    fclose(file);

    // Verifica se perguntas foram lidas
    if (total_perguntas == 0) {
        printf("Nenhuma pergunta foi lida do arquivo: %s\n", nome_arquivo);
    }
}

void perguntas_facil() {
    ler_perguntas("question_easy.txt");
    embaralhar_perguntas();
}

void perguntas_medio() {
    ler_perguntas("question_medium.txt");
    embaralhar_perguntas();
}

void perguntas_dificil() {
    ler_perguntas("question_hard.txt");
    embaralhar_perguntas();
}

void jogar(int dificuldade) {
    if (total_perguntas == 0) {
        printf("Não há perguntas disponíveis para jogar.\n");
        return;
    }

    char resp;
    for (int i = 0; i < total_perguntas; i++) {
        printf("\nPergunta %d: %s\n", i + 1, enunciado[i]);
        for (int j = 0; j < MAX_ALTERNATIVAS; j++) {
            printf(" %c) %s\n", 'a' + j, alternativas[i][j]);
        }
        printf("Digite sua resposta: ");
        resp = getchar();
        limpar_buffer(); // Limpa o buffer após a entrada

        if (resp == resp_correta[i]) {
            printf("Certa resposta!\n");
        } else {
            printf("Resposta errada! A resposta correta era: %c\n", resp_correta[i]);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int dificuldade;

    do {
        printf("\n------Bem-vindo ao jogo!!!-----\n");
        printf("\n------Digite ENTER para continuar------\n");
        getchar();
        limpar_buffer();
        limpar_tela();
        printf("\n----- Escolha a dificuldade -----\n");
        printf("1 - Fácil\n");
        printf("2 - Médio\n");
        printf("3 - Difícil\n");
        scanf("%d", &dificuldade);
        limpar_buffer(); // Limpar o buffer após ler a dificuldade

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
