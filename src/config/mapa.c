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
    
    jogo -> qtdLinhas = qtd_linhas;

    fclose(meu_arquivo); 
    
    // Imprime para confirmar
    printf("Mapa carregado com sucesso (%d linhas):\n", qtd_linhas);
    for (int i = 0; i < qtd_linhas; i++) {
        printf("%s\n", jogo -> mapa[i]);
    }
}

// feito por gb 
void Encontrar_Entidades (Estado_jogo *jogo ){
jogo->qtdFantasmas = 0;
    int linha, coluna;
    for (linha = 0; linha < jogo->qtdLinhas; linha++){
        for (coluna = 0; coluna <strlen(jogo->mapa[linha]); coluna++){
            if (jogo-> mapa[linha][coluna]=='P'){
                jogo -> jogador.x = coluna;
                jogo -> jogador.y = linha;
            }
            if (jogo ->mapa[linha][coluna]=='G'){
                jogo-> fantasmas[jogo->qtdFantasmas].pos.x = coluna;
                jogo-> fantasmas[jogo->qtdFantasmas].pos.y = linha;
                jogo->qtdFantasmas ++;
            }
        }
    }
    //testes
    printf("\n jogador: x=%d y=%d \n", jogo->jogador.x , jogo->jogador.y);
    printf("fantasma 0: x=%d y=%d\n", jogo->fantasmas[0].pos.x, jogo->fantasmas[0].pos.y);
    printf("fantasma 1: x=%d y=%d\n", jogo->fantasmas[1].pos.x, jogo->fantasmas[1].pos.y);
}

void contar_pontos (Estado_jogo *jogo){
    int linha, coluna;
    jogo->pontosRestantes = 0;
    jogo->pontosColetados = 0;
    for (linha = 0; linha < jogo->qtdLinhas; linha++){
        for (coluna = 0; coluna <strlen(jogo->mapa[linha]); coluna++){
            if (jogo -> mapa[linha][coluna]=='.'){
                jogo-> pontosRestantes ++;
            }
        }
    }
    printf("Pontos Restantes: %d \n", jogo->pontosRestantes);
}


