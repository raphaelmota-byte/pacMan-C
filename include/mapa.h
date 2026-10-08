// As guardas de inclusão evitam que o cabeçalho seja lido duas vezes
#ifndef MAPA_H
#define MAPA_H

#include "estado.h" //o mapa deve conhecer o estado do jogo


void carregar_cenario(Estado_jogo *jogo, char *caminhoArquivo);
void sortear_caminho_mapa(char *caminho);

#endif