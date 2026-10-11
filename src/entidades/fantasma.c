#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entidades.h"
#include "mapa.h"

// Função auxiliar: Sorteia um movimento válido (usada no modo fácil e no fallback do difícil)
void sortear_direcao_valida(Estado_jogo *jogo, int indice, int *prox_x, int *prox_y) {
    int x_atual = jogo->fantasmas[indice].pos.x;
    int y_atual = jogo->fantasmas[indice].pos.y;
    
    do {
        // Reseta para a origem usando os ponteiros
        *prox_x = x_atual;
        *prox_y = y_atual;
        
        int direcao = rand() % 4; 
        switch (direcao) {
            case 0: (*prox_y)--; break; 
            case 1: (*prox_y)++; break; 
            case 2: (*prox_x)--; break; 
            case 3: (*prox_x)++; break; 
        }
    } while (!eh_movimento_valido(jogo, *prox_x, *prox_y) || jogo->mapa[*prox_y][*prox_x] == 'G');
}


// Função auxiliar: Apenas executa a movimentação física no mapa
void aplicar_movimento_fantasma(Estado_jogo *jogo, int indice, int proximo_x, int proximo_y) {
    int x_atual = jogo->fantasmas[indice].pos.x;
    int y_atual = jogo->fantasmas[indice].pos.y;

    // Deixa o mapa da mesma forma que estava antes
    jogo->mapa[y_atual][x_atual] = jogo -> fantasmas[indice].itemAnterior;

    // Protege a memória do novo local (não clona o 'P' nem outro 'G')[cite: 8]
    char item_destino = jogo -> mapa[proximo_y][proximo_x];
    if (item_destino == 'P' || item_destino == 'G') {
        jogo->fantasmas[indice].itemAnterior = ' ';
    } else {
        jogo->fantasmas[indice].itemAnterior = item_destino;
    }
    
    jogo->fantasmas[indice].pos.x = proximo_x;
    jogo->fantasmas[indice].pos.y = proximo_y;

    jogo->mapa[proximo_y][proximo_x] = 'G';
}

void mover_fantasma_aleatorio(Estado_jogo *jogo, int indice_fantasma) {
    int proximo_x , proximo_y;

    // 1. Pede para o helper sortear a direção (passando o endereço & das variáveis)
    sortear_direcao_valida(jogo, indice_fantasma, &proximo_x, &proximo_y);
    
    // 2. Aplica o movimento
    aplicar_movimento_fantasma(jogo, indice_fantasma, proximo_x, proximo_y);

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