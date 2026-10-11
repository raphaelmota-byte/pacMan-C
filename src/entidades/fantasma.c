#include "entidades.h"


void mover_fantasma_aleatorio(Estado_jogo *jogo, int indice_fantasma) {
    // Lógica do rand() % 4 para o fantasma específico
}

void mover_fantasma_perseguidor(Estado_jogo *jogo, int indice_fantasma) {
    // Lógica de cálculo de distância (Delta X e Delta Y) para o fantasma específico
}

void mover_todos_fantasmas(Estado_jogo *jogo) {
    for (int i = 0; i < jogo->qtdFantasmas; i++) {
        if (jogo->dificuldade == 1) {
            mover_fantasma_aleatorio(jogo, i);
        } else {
            mover_fantasma_perseguidor(jogo, i);
        }
    }
}