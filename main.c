#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "estilizacao.h"

#define MAX_PERGUNTAS 16
#define MAX_ALTERNATIVAS 4
#define MAX_TAM 512
#define MAX_nome 20
#define MAX_jogadores 100

char enunciado[MAX_PERGUNTAS][MAX_TAM];
char alternativas[MAX_PERGUNTAS][MAX_ALTERNATIVAS][MAX_TAM];
char resp_correta[MAX_PERGUNTAS];
int total_perguntas = 0;
char nome[21];
char next, resp;
int numero_de_perguntas = 1, pontos = 0 ;//jogador escolhe a quantidade de perguntas

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
    if (numero_de_perguntas == 0) {
        printf("Não há perguntas disponíveis para jogar.\n");
        return;
    }
    for (int i = 0; i < numero_de_perguntas; i++) {
        printf("\nPergunta %d: %s\n", i + 1, enunciado[i]);
        for (int j = 0; j < 4; j++) {
            printf(" %c) %s\n", 'a' + j, alternativas[i][j]);
        }
        printf("Digite sua resposta: ");
        resp = getchar();
        limpar_buffer(); // Limpa o buffer após a entrada
        limpar_tela();//limpa a tela depois de cada pergunta

        if (resp == resp_correta[i]) {
            printf("Certa resposta!\n");
            switch(dificuldade){
                case 1:
                pontos += 5;//recebe 5 pontos por pergunta facil
                break;
                case 2:
                pontos += 7;//7 pontos por pergunta media
                break;
                case 3:
                pontos += 13;//13 pontos por pergunta dificil
                break;
            }
            right_music("moutain_trails.wav,0,5");

        } else {
            printf("Resposta errada! A resposta correta era: %c\n", resp_correta[i]);
            switch(dificuldade){
                case 1:
                pontos -= 3;//penaliza o jogador
                break;
                case 2:
                pontos -= 5;
                break;
                case 3:
                pontos -= 11;
                break;
            }
            right_music("a_night_of_dizzy_spells.wav", 0,5);
        }
    }
}
//estrtura para armazenar o nome e pontuação de cada jogador
typedef struct {
    char nome[MAX_nome];
    int pontos;
} Jogador;
//Atualiza o ranking em ordem decrescente
void atualizarRanking(const char *nome, int pontos) {
    Jogador jogadores[MAX_jogadores];
    int numJogadores = 0;

    // Lê o arquivo existente
    FILE *arquivo = fopen("ranking.txt", "r");
    if (arquivo != NULL) {
        while (fscanf(arquivo, "%s %d", jogadores[numJogadores].nome, &jogadores[numJogadores].pontos) == 2) {
            numJogadores++;
            if (numJogadores >= MAX_jogadores) {
                break; // Evita overflow
            }
        }
        fclose(arquivo);
    } else {
        printf("ERROR ao abrir o arquivo\n");
    }

    // Adiciona o novo jogador
    strncpy(jogadores[numJogadores].nome, nome, MAX_nome - 1);
    jogadores[numJogadores].nome[MAX_nome - 1] = '\0'; // Garante que a string esteja terminada
    jogadores[numJogadores].pontos = pontos;
    numJogadores++;

    // Classifica os jogadores em ordem decrescente
    for (int i = 0; i < numJogadores - 1; i++) {
        for (int j = 0; j < numJogadores - i - 1; j++) {
            if (jogadores[j].pontos < jogadores[j + 1].pontos) {
                // Troca os jogadores
                Jogador temp = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = temp;
            }
        }
    }

    // Escreve de volta no arquivo
    arquivo = fopen("ranking.txt", "w");
    if (arquivo != NULL) {
        for (int i = 0; i < numJogadores; i++) {
            fprintf(arquivo, "%s %d\n", jogadores[i].nome, jogadores[i].pontos);
        }
        fclose(arquivo);
    } else {
        printf("ERROR ao abrir o arquivo\n");
    }
}

void mostrarRanking() {
    FILE *arquivo = fopen("ranking.txt", "r");
    if (arquivo != NULL) {
        char nome[MAX_nome];
        int pontos;
        printf("Ranking:\n");
        while (fscanf(arquivo, "%20s %d", nome, &pontos) != EOF) {
            printf("%s: %d\n", nome, pontos);
        }
        fclose(arquivo);
    } else {
        printf("ERROR ao abrir o arquivo\n");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int dificuldade;
    iniciar_mixer();
    play_music("night_shade.wav");

    do {
        void tela_inicial();
        void loop_jogo();
        printf("\n------Bem-vindo ao jogo!!!-----\n");
        printf("\n------Digite ENTER para continuar------\n");
        getchar();
        limpar_buffer();
        limpar_tela();
        printf("Digite seu nome:\n(ate 20 caracteres)\n");
        scanf("%s",&nome);
        printf("Escolha o número de perguntas:\n(Um número entre 1 e 16)\n");
        scanf("%d",&numero_de_perguntas);
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
        printf("\n%s : %d pontos", nome, pontos);
        printf("\ndeseja continuar?\n");
        printf("S-sim\nN-nao\n");
        scanf("%s",&next);
        limpar_tela();
        //atualiza o ranking
        atualizarRanking(nome,pontos);
        //mostrar o ranking ao final do jogo
        mostrarRanking();
        pontos = 0;
    } while (next == 's' || next == 'S');

    return 0;
}
