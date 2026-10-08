// As guardas de inclusão evitam que o cabeçalho seja lido duas vezes
#ifndef MAPA_H
#define MAPA_H

#include "estado.h"


void carregar_cenario(char mapa[MAX_LINHAS][MAX_COLUNAS], char *caminhoArquivo);
void sortear_caminho_mapa(char *caminho);

#endif