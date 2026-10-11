#include "regras.h"

int verificar_colisao(Estado_jogo *jogo) {
    for (int i = 0; i < jogo->qtdFantasmas; i++) {
        if (jogo->jogador.x == jogo->fantasmas[i].pos.x &&
            jogo->jogador.y == jogo->fantasmas[i].pos.y) {
            return 1; // Colidiu
        }
    }
    return 0; 
}

int verificar_vitoria(Estado_jogo *jogo) {
    if (jogo->pontosRestantes == 0) {
        return 1; // Venceu
    }
    return 0;
}