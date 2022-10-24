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

    lista *L;
    no *N;

    FILE *leitor;
    FILE *compac;

    leitor = fopen("teste.txt", "r");
    char aux;
    while (!feof(leitor)) {
         fscanf(leitor, "%c", &aux);
         tab[aux]++;
    }
    fclose (leitor);

    cria_lista(L);
    cria_no(L, tab);

    no *aux2;
    aux2 = L->raiz;

/*    
    //teste
    while (aux2->prox) {
        printf("%d, %c\n", aux2->valor.peso, aux2->valor.letra);
        aux2 = aux2->prox;
    }
*/  

return 0;
}