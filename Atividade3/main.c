#include <stdio.h>
#include <stdlib.h>
#include "functions.c"

#define bool int
#define true 1
#define false 0
#define MAX 256

int main()  {

    unsigned int tab[MAX]; //tabela de frequencia
    inicializa_tab(tab);

    lista *List;

    FILE *leitor;
    FILE *compac;

    leitor = fopen("teste.txt", "r");

    char aux;
    while (!feof(leitor)) {
         fscanf(leitor, "%c", &aux);
         tab[aux]++;
    }

    cria_lista(List);

    cria_no(List, tab);


    fclose(leitor);
return 0;
}