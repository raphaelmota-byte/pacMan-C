#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entidades.h"
#include "mapa.h"


void mover_fantasma_aleatorio(Estado_jogo *jogo, int indice_fantasma) {
    int x_atual = jogo->fantasmas[indice_fantasma].pos.x;
    int y_atual = jogo->fantasmas[indice_fantasma].pos.y;
    
    int proximo_x;
    int proximo_y;
    
    // 1. Deixa o mapa igual quando o fantasma não estava lá
    jogo->mapa[y_atual][x_atual] = jogo->fantasmas[indice_fantasma].itemAnterior;

    // 2. Sorteia até achar um caminho livre
    do {
        // Traz as coordenadas de volta para a origem a cada nova tentativa
        proximo_x = x_atual;
        proximo_y = y_atual;
        
        int direcao = rand() % 4; // 0=Cima, 1=Baixo, 2=Esquerda, 3=Direita[cite: 3]
    
        switch (direcao) {
            case 0: proximo_y--; break; 
            case 1: proximo_y++; break; 
            case 2: proximo_x--; break; 
            case 3: proximo_x++; break; 
        }

    } while (!eh_movimento_valido(jogo, proximo_x, proximo_y) || jogo->mapa[proximo_y][proximo_x] == 'G');

    // 3. Salva o que tem na NOVA casa antes do fantasma pisar
    jogo->fantasmas[indice_fantasma].itemAnterior = jogo->mapa[proximo_y][proximo_x];

    // 4. Atualiza a struct do fantasma
    jogo->fantasmas[indice_fantasma].pos.x = proximo_x;
    jogo->fantasmas[indice_fantasma].pos.y = proximo_y;

    // 5. Atualiza o mapa com o 'G'
    jogo->mapa[proximo_y][proximo_x] = 'G';



    
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