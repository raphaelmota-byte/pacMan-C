#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para srand()
#include <time.h> // para time()

#include "estado.h"
#include "mapa.h"
#include "entidades.h"

int main() {

    // Inicialização da semente aleatória com srand(time(NULL)) para garantir escolhas distintas a cada execução do jogo
    // Sem isso, a função rand() repetiria sempre a mesma sequência de mapas.
    srand(time(NULL)); 
    Estado_jogo meu_jogo;
    char caminho_sorteado[50]; // String vazia para receber o caminho
    
    sortear_caminho_mapa(caminho_sorteado);
    carregar_cenario(&meu_jogo, caminho_sorteado);
    Encontrar_Entidades(&meu_jogo);
    contar_pontos(&meu_jogo);
    
    // Exibe o mapa na tela pela primeira vez
    exibir_mapa(&meu_jogo);

    int tecla;
    do {
        printf("\nInsira as teclas de movimento (w, a, s, d) ou q para parar: ");
        tecla = captura_tecla(); 
        
        // Verifica se é uma tecla de movimento válida
        if (tecla == 'w' || tecla == 'a' || tecla == 's' || tecla == 'd') {
            
            // --- ORQUESTRAÇÃO FUTURA DAS FUNÇÕES ---
            // mover_jogador(&meu_jogo, tecla);
            // mover_fantasmas(&meu_jogo);
            
            // Atualiza a tela após processar a rodada
            exibir_mapa(&meu_jogo);
            
        } else if (tecla != 'q') {
            printf("\nTecla nao reconhecida. Tente w, a, s, d.\n");
        }
        
    } while (tecla != 'q');
    
    printf("\nJogo encerrado!\n");


  

    return 0;
}