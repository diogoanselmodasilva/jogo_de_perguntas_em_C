#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define MAX_PERGUNTAS 16
#define MAX_ALTERNATIVAS 4
#define MAX_TAM 512
#define MAX_nome 20
#define MAX_jogadores 100

char enunciado[MAX_PERGUNTAS][MAX_TAM];
char alternativas[MAX_PERGUNTAS][MAX_ALTERNATIVAS][MAX_TAM];
char resp_correta[MAX_PERGUNTAS];
int total_perguntas = 1;//perguntas deve começar ao menos em 1
char nome[21];
char next, resp;
int numero_de_perguntas = 1, pontos = 1 , posicao, modo = 1;
//jogador escolhe a quantidade de perguntas, pontuacao e posicao do jogadoor

// Função para limpar o buffer
void limpar_buffer() {
     #ifdef _WIN32
        flush(stdin);
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
//função para abrir o arquivo e ler as perguntas
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
//pega as perguntas do arquivo por dificuldade
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
//estrtura para armazenar o nome e pontuação de cada jogador
typedef struct {
    int posicao;
    char nome[MAX_nome];
    int pontos;
} Jogador;
//aqui é a mecanica do jogo por dificuldade
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
                case 1: pontos += 5;//recebe 5 pontos por pergunta facil
                break;
                case 2: pontos += 7;//7 pontos por pergunta media
                break;
                case 3: pontos += 13;//13 pontos por pergunta dificil
                break;
            }

        } else {
            printf("Resposta errada! A resposta correta era: %c\n", resp_correta[i]);
            switch(dificuldade){
                case 1: pontos -= 3;//penaliza o jogador
                break;
                case 2: pontos -= 5;
                break;
                case 3: pontos -= 11;
                break;
            }
        }
    }
}
//para jogar 2 jogadores
void jogar_multiplayer(Jogador *jogador1, Jogador *jogador2, int numero_de_perguntas, int dificuldade) {
    for (int i = 0; i < numero_de_perguntas; i++) {
        for (int j = 0; j < 2; j++) {
            Jogador *jogador_atual = (j == 0) ? jogador1 : jogador2;
            printf("\nPergunta %d para %s: %s\n", i + 1, jogador_atual-> nome, enunciado[i]);
            for (int k = 0; k < 4; k++) {
                printf(" %c) %s\n", 'a' + k, alternativas[i][k]);
            }
            printf("Digite sua resposta: ");
            char resp = getchar();
            limpar_buffer();

            if (resp == resp_correta[i]) {
                printf("Certa resposta!\n");
                switch(dificuldade){
                case 1: jogador_atual -> pontos += 5;//recebe 5 pontos por pergunta facil
                break;
                case 2: jogador_atual -> pontos += 7;//7 pontos por pergunta media
                break;
                case 3: jogador_atual -> pontos += 13;//13 pontos por pergunta dificil
                break;
            }
            }
                else {
                    printf("Resposta errada! A resposta correta era: %c\n", resp_correta[i]);
                    switch(dificuldade){
                        case 1: jogador_atual -> pontos -= 3;//penaliza o jogador
                        break;
                        case 2: jogador_atual -> pontos -= 5;
                        break;
                        case 3: jogador_atual -> pontos -= 11;
                        break;
                    }
            }
        }
    }
}
//Atualiza o ranking em ordem decrescente
void atualizarRanking(const char *nome, int pontos) {
    Jogador jogadores[MAX_jogadores];
    int numJogadores = 0;
    // Lê o arquivo existente
    FILE *arquivo = fopen("ranking.txt", "r");
    if (arquivo != NULL) {
        while (fscanf(arquivo, "%d %s %d", &jogadores[numJogadores].posicao, jogadores[numJogadores].nome, &jogadores[numJogadores].pontos) == 3) {
            numJogadores++;
            if (numJogadores >= MAX_jogadores) {
                break;
            }
        }
        fclose(arquivo);
    } else {
        printf("ERROR ao abrir o arquivo\n");
    }
    // Adiciona o novo jogador
    Jogador novoJogador;
    strncpy(novoJogador.nome, nome, MAX_nome - 1);
    novoJogador.nome[MAX_nome - 1] = '\0';  // Garante que a string esteja terminada
    novoJogador.pontos = pontos;
    jogadores[numJogadores] = novoJogador;
    numJogadores++;

    // Classifica os jogadores em ordem decrescente
    for (int i = 0; i < 10 - 1; i++) {
        for (int j = 0; j < 10 - i - 1; j++) {
            if (jogadores[j].pontos < jogadores[j + 1].pontos) {
                // Troca os jogadores
                Jogador temp = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = temp;
            }
        }
    }
    // Atualiza as posições
    for (int i = 0; i < 10; i++) {
        jogadores[i].posicao = i + 1;
    }
    // Escreve de volta no arquivo
    arquivo = fopen("ranking.txt", "w");
    if (arquivo != NULL) {
        for (int i = 0; i < 10; i++) {
            fprintf(arquivo, "%d %s %d\n", jogadores[i].posicao, jogadores[i].nome, jogadores[i].pontos);
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
        int posicao;
        int pontos;
        printf("Ranking:\n");
        while (fscanf(arquivo, "%%d %s %d", &posicao, nome, &pontos) != EOF) {
            printf("%d- %s: %d pontos\n", posicao, nome, pontos);
        }
        fclose(arquivo);
    } else {
        printf("ERROR ao abrir o arquivo\n");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int dificuldade;
    system("night_shade.mpeg");

    do {
        printf("\n------Bem-vindo ao jogo!!!-----\n");
        printf("\n------Digite ENTER para continuar------\n");
        getchar();
        limpar_buffer();
        limpar_tela();
        printf("\nEscolha o modo do jogo:\n");
        printf("\n1-Sozinho \n2-Dupla\n");
        scanf("%d", &modo);
        if(modo == 1){
            printf("Digite seu nome:\n(ate 20 caracteres)\n");
            scanf("%s",nome);
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
            scanf("%c",&next);
            limpar_tela();
            //atualiza o ranking
            atualizarRanking(nome,pontos);
            //mostrar o ranking ao final do jogo
            mostrarRanking();
            pontos = 0;
        }
        if(modo == 2){
            Jogador jogadores[2]; // 2 jogadores
            printf("Digite o nome do jogador 1: ");
            scanf("%s", jogadores[0].nome);
            limpar_buffer();
            printf("Digite o nome do jogador 2: ");
            scanf("%s", jogadores[1].nome);

            // Inicializa os pontos
            jogadores[0].pontos = 0;
            jogadores[1].pontos = 0;

            printf("Escolha o número de perguntas:\n(Um número entre 1 e 16)\n");
            scanf("%d", &numero_de_perguntas);

            printf("\n----- Escolha a dificuldade -----\n");
            printf("1 - Fácil\n");
            printf("2 - Médio\n");
            printf("3 - Difícil\n");
            scanf("%d", &dificuldade);
            limpar_buffer(); // Limpar o buffer após ler a dificuldade
            limpar_tela();

            // Para jogar multiplayer
            switch (dificuldade) {
                case 1:
                    perguntas_facil();
                    jogar_multiplayer(&jogadores[0], &jogadores[1], numero_de_perguntas,dificuldade);
                    break;
                case 2:
                    perguntas_medio();
                    jogar_multiplayer(&jogadores[0], &jogadores[1], numero_de_perguntas,dificuldade);
                    break;
                case 3:
                    perguntas_dificil();
                    jogar_multiplayer(&jogadores[0], &jogadores[1], numero_de_perguntas,dificuldade);
                    break;
                default:
                    printf("Por favor, escolha um nível de dificuldade válido!\n");
                    break;
            }

            // Mostrar a pontuação dos jogadores
            printf("%s : %d pontos\n", jogadores[0].nome, jogadores[0].pontos);
            printf("%s : %d pontos\n", jogadores[1].nome, jogadores[1].pontos);

            // Outra rodada ou não
            printf("\ndeseja continuar?\n");
            printf("S-sim\nN-nao\n");
            scanf(" %c", &next); // Note o espaço antes de %c para evitar problemas com o buffer
            limpar_tela();

            // Atualiza o ranking
            atualizarRanking(jogadores[0].nome, jogadores[0].pontos);
            atualizarRanking(jogadores[1].nome, jogadores[1].pontos);

            // Mostrar o ranking ao final do jogo
            mostrarRanking();
            pontos = 0; // Reseta os pontos para a próxima rodada

        }
    } while (next == 's' || next == 'S');
    return 0;
}
