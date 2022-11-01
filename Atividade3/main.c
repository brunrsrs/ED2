#include <stdio.h>
#include <stdlib.h>
#include "functions.c"

#define bool int
#define true 1
#define false 0
#define MAX 256

int main()  {
    char **dicionario; //onde será armazenado cada valor de char

    unsigned int tab[MAX]; //tabela de frequencia
    inicializa_tab(tab);

    lista *L = malloc(sizeof(lista));
    no *N, *arvore;

    FILE *leitor;
    FILE *compac;

    leitor = fopen("teste.txt", "r");
    char aux;
    while (!feof(leitor)) {
         aux = fgetc(leitor);
         tab[aux]++;
    }
    fclose (leitor);

    cria_lista(L);
    preenche_lista(L, tab);

    arvore = montar_arvore(L);
    imprimir_arvore(arvore, 0);

return 0;
}