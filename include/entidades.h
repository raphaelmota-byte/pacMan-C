#ifndef JOGADOR_H
#define JOGADOR_H

#include "estado.h"

int captura_tecla (void);
void mover_jogador(Estado_jogo *jogo, int tecla);

void mover_fantasma_aleatorio(Estado_jogo *jogo, int indice_fantasma);
void mover_fantasma_perseguidor(Estado_jogo *jogo, int indice_fantasma);
void mover_todos_fantasmas(Estado_jogo *jogo);

#endif
