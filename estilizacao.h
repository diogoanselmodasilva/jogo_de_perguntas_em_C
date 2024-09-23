#ifndef ESTILIZACAO_H
#define ESTILIZACAO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// Função para criar a tela inicial
void iniciar_mixer();
void tela_inicial();
void playmusic(const char *caminho_musica);
void right_music();

#endif // ESTILIZACAO_H
