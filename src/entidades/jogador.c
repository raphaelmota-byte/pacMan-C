#include "entidades.h"
#include <ctype.h>  // tolower(): aceita 'w' e 'W' do mesmo jeito
#include <conio.h>  // _getch(): lê a tecla sem precisar de Enter

#include "mapa.h"

int captura_tecla (void){
     int tecla = _getch();
     tecla = tolower(tecla);
    return tecla;
 }


void mover_jogador(Estado_jogo *jogo, int tecla) {
    // 1. Descobre a posição atual do jogador
    int proximo_x = jogo->jogador.x;
    int proximo_y = jogo->jogador.y;

    // 2. Calcula a intenção de movimento
    switch (tecla) {
        case 'w': proximo_y--; break; // Sobe uma linha
        case 's': proximo_y++; break; // Desce uma linha
        case 'a': proximo_x--; break; // Vai para a coluna da esquerda
        case 'd': proximo_x++; break; // Vai para a coluna da direita
        default: return; // Se for outra tecla, ignora
    }

    // Pergunta ao mapa se o movimento é válido
    if (eh_movimento_valido(jogo, proximo_x, proximo_y)) {
        
        // Apaga o jogador da posição antiga na matriz
        jogo->mapa[jogo->jogador.y][jogo->jogador.x] = ' '; 
        
        // Atualiza as coordenadas na struct
        jogo->jogador.x = proximo_x;
        jogo->jogador.y = proximo_y;

        if (jogo-> mapa[jogo->jogador.y][jogo->jogador.x] == '.'){
            jogo -> pontosColetados ++ ;
            jogo -> pontosRestantes-- ;

        }
        
        // Desenha o jogador na nova posição da matriz
        jogo->mapa[jogo->jogador.y][jogo->jogador.x] = 'P';
    }
}