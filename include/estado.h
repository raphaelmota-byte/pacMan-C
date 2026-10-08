//necessario para garantir que tudo dentro do arquivo seja criado apenas uma vez na memoria
//sem ele cada arquivo que importasse esse criaria um novo espaaço na memoria e resultaria em error
#ifndef ESTADO_H //if not define ESTADO_H:

#define ESTADO_H

#define MAX_LINHAS 100
#define MAX_COLUNAS 100

typedef struct 
{
   int x;
   int y;
}Posicao;

typedef struct 
{
    Posicao pos ;
    char itemAnterior; // Guarda o que estava no mapa ('.' ou ' ') antes do fantasma passar

}Fantasma;


typedef struct{
    char mapa[MAX_LINHAS][MAX_COLUNAS];
    Posicao jogador;
    Fantasma fantasmas[10];
    int qtdFantasmas;
    int pontosColetados;
    int pontosRestantes;
    int dificuldade; // 1 = Fácil, 2 = Difícil
}Estado_jogo;



#endif