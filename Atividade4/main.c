#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atividade4.c"

int main() {
int op=0;
FILE *arqDados, *arqIndice;

do {
    Menu();
    printf("Comando: ");
    scanf(" %d", &op);

    switch(op) {
        case 1:
        break;

        case 2:
        break;

        case 3:
        break;

        default:
            printf("\n\tValor inválido\n");
        break;
    }


} while(op!=3);


return 0;
}