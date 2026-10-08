#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para rand() e srand()
#include <time.h> // para time()
#include "mapa.h" // Usamos aspas duplas para importar nossos próprios .h


void sortear_caminho_mapa(char *caminho) {
    // rand() % 3 gera números de 0 a 2. Somamos 1 para ficar de 1 a 3
    int numero_sorteado = (rand() % 3) + 1; 
    
    // Monta a string dinamicamente e salva na variável "caminho"
    sprintf(caminho, "data/mapa_%d.txt", numero_sorteado);
    
    printf("Mapa sorteado: %s\n", caminho);
}


void carregar_cenario(Estado_jogo *jogo, char *caminhoArquivo){
    int qtd_linhas = 0;
    
   
    FILE *meu_arquivo = fopen(caminhoArquivo, "r"); 
    
    if (meu_arquivo == NULL) {
        printf("Erro ao carregar o mapa do caminho: %s\n", caminhoArquivo);
        return; // Interrompe a função aqui para não dar erro no fgets
    }
    
    // Lemos o arquivo linha por linha usando o fgets
    while (fgets(jogo -> mapa[qtd_linhas], MAX_COLUNAS, meu_arquivo) != NULL) {
        
        // removendo o '\n' (quebra de linha) e substitui por '\0'
        jogo -> mapa[qtd_linhas][strcspn(jogo -> mapa[qtd_linhas], "\n")] = '\0';
        
        qtd_linhas++; 
    }
    
    fclose(meu_arquivo); 
    
    // Imprime para confirmar
    printf("Mapa carregado com sucesso (%d linhas):\n", qtd_linhas);
    for (int i = 0; i < qtd_linhas; i++) {
        printf("%s\n", jogo -> mapa[i]);
    }
}

