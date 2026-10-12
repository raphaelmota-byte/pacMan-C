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
    int x_atual = jogo->fantasmas[indice_fantasma].pos.x;
    int y_atual = jogo->fantasmas[indice_fantasma].pos.y;
    
    // 1. Calcula a distância Absoluta (Delta) em X e Y
    int delta_x = abs(jogo->jogador.x - x_atual);
    int delta_y = abs(jogo->jogador.y - y_atual);
    
    int passo_x = (jogo->jogador.x > x_atual) ? 1 : -1;
    int passo_y = (jogo->jogador.y > y_atual) ? 1 : -1;

    int proximo_x = x_atual;
    int proximo_y = y_atual;
    int moveu = 0;

    // 2. Identifica o Eixo Dominante e tenta o movimento[cite: 2]
    if (delta_x > delta_y) {
        // Tenta primeiro se mover na horizontal (Eixo dominante X)[cite: 2]
        if (eh_movimento_valido(jogo, x_atual + passo_x, y_atual) && jogo->mapa[y_atual][x_atual + passo_x] != 'G') {
            proximo_x += passo_x; 
            moveu = 1;
        } 
        // Se o movimento no eixo dominante for bloqueado por uma parede, tenta o eixo secundário[cite: 2]
        else if (eh_movimento_valido(jogo, x_atual, y_atual + passo_y) && jogo->mapa[y_atual + passo_y][x_atual] != 'G') {
            proximo_y += passo_y; 
            moveu = 1;
        }
    } else {
        // Tenta primeiro se mover na vertical (Eixo dominante Y)
        if (eh_movimento_valido(jogo, x_atual, y_atual + passo_y) && jogo->mapa[y_atual + passo_y][x_atual] != 'G') {
            proximo_y += passo_y; 
            moveu = 1;
        } 
        // Se o movimento no eixo dominante for bloqueado por uma parede, tenta o eixo secundário[cite: 2]
        else if (eh_movimento_valido(jogo, x_atual + passo_x, y_atual) && jogo->mapa[y_atual][x_atual + passo_x] != 'G') {
            proximo_x += passo_x; 
            moveu = 1;
        }
    }

    // 3. Mecanismo Anti-Travamento (Fallback)[cite: 2]
    // Se ambos os eixos estiverem bloqueados, escolhe uma direção aleatória para desviar usando a nova função com ponteiros[cite: 2]
    if (!moveu) {
        sortear_direcao_valida(jogo, indice_fantasma, &proximo_x, &proximo_y);
    }

    // 4. Delega o "Agir": aplica a movimentação física no labirinto
    aplicar_movimento_fantasma(jogo, indice_fantasma, proximo_x, proximo_y);
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