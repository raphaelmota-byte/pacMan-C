#include <stdio.h>
#include "core.h"
#include "jogador.h"

void loop_jogo(Estado_jogo *jogo) {
    int tecla;
    // 'q' eh a condicao de parada
    printf("\ninsira as teclas de movimento (w , a ,s ,d) ou q para parar: ");
    do {
        tecla = captura_tecla();
        printf("\nVoce apertou: %c\n", tecla);
        if (tecla != 'a' && tecla !='w' && tecla !='s' && tecla !='d'&& tecla != 'q' ){
            printf("Tecla nao reconhecida.\ninsira uma tecla de movimento valida (w , a ,s ,d) ou q para parar:\n");
        }
    } while (tecla != 'q');
}