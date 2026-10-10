#include "jogador.h"
#include <ctype.h>  // tolower(): aceita 'w' e 'W' do mesmo jeito
#include <conio.h>  // _getch(): lê a tecla sem precisar de Enter

 int captura_tecla (void){
     int tecla = _getch();
     tecla = tolower(tecla);
    return tecla;
 }