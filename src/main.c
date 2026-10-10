#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para srand()
#include <time.h> // para time()
#include "mapa.h" // Usamos aspas duplas para importar nossos próprios .h
#include "core.h"



int main() {

    // Inicialização da semente aleatória com srand(time(NULL)) para garantir escolhas distintas a cada execução do jogo
    // Sem isso, a função rand() repetiria sempre a mesma sequência de mapas.
    srand(time(NULL)); 
    Estado_jogo meu_jogo;
    
    char caminho_sorteado[50]; // String vazia para receber o caminho
    
    // 1. Sorteia o caminho e salva na string
    sortear_caminho_mapa(caminho_sorteado);
    
    // 2. Carrega o cenário usando a string sorteada
    carregar_cenario(&meu_jogo, caminho_sorteado);

    // 3.encontra jogador e fantasmas no mapa
    // x = coluna e y= linha
    Encontrar_Entidades (&meu_jogo);

    // 4. conta quantos pontos restam para serem pegos
    contar_pontos (&meu_jogo);

    //5. limpa o terminal anterior , imprime o mapa com os placares de pontos (restantes e pegos)
    exibir_mapa (&meu_jogo);

    // mantem a tecla em loop
    loop_jogo(&meu_jogo);

   
   
    return 0;
}