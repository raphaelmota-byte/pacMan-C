#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para srand()
#include <time.h> // para time()
#include "mapa.h" 


int main() {

    // Inicialização da semente aleatória com srand(time(NULL)) para garantir escolhas distintas a cada execução do jogo
    // Sem isso, a função rand() repetiria sempre a mesma sequência de mapas.
    srand(time(NULL)); 
    
    char meu_labirinto[MAX_LINHAS][MAX_COLUNAS];
    char caminho_sorteado[50]; // String vazia para receber o caminho
    
    // 1. Sorteia o caminho e salva na string
    sortear_caminho_mapa(caminho_sorteado);
    
    // 2. Carrega o cenário usando a string sorteada
    carregar_cenario(meu_labirinto, caminho_sorteado);


    return 0;
}