#include "estilizacao.h"
#include <stdio.h>
#include <stdbool.h>

void tela_inicial() {
    SDL_Window *janela = NULL;
    SDL_Renderer *renderizador = NULL;
    SDL_Event eventos;
    int executando = 1;

    // Inicializa a SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return;
    }

    // Cria a janela
    janela = SDL_CreateWindow("Tela Inicial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (janela == NULL) {
        printf("Erro ao criar a janela: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    // Cria o renderizador
    renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);
    if (renderizador == NULL) {
        printf("Erro ao criar o renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(janela);
        SDL_Quit();
        return;
    }

    // Loop de execução
    while (executando) {
        while (SDL_PollEvent(&eventos)) {
            if (eventos.type == SDL_QUIT) {
                executando = 0;
            }
        }

        // Limpa a tela com uma cor (preto)
        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
        SDL_RenderClear(renderizador);
        SDL_RenderPresent(renderizador);
    }

    // Limpa recursos
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    SDL_Quit();
}
