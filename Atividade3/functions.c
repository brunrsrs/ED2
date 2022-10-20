#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define bool int
#define true 1
#define false 0
#define MAX 256

void inicializa_tab(unsigned int t[]) {
    for (int i=0; i<MAX; i++) {
        t[i] = 0;
    }
}

//inicializa a lista
void cria_lista(lista *L) {
    L->tam = 0; 
    L->raiz = NULL;
}

//cria o nó com as informações
void cria_no(lista *L, unsigned int t[]) {
    arvore *novo;
    for (int i=0; i<MAX; i++) {
        if (t[i] != 0) {
            novo = malloc(sizeof(arvore));
            if (novo) {
                novo->dir = NULL;
                novo->prox = NULL;
                novo->esq = NULL;
                novo->raiz.letra = i;
                novo->raiz.peso = t[i];

                //inserir

                //testando
                //printf("\npeso = %d\nchar = %c\n", novo->raiz.peso, novo->raiz.letra);

            }
            else {
                printf("Não foi possivel alocar memoria");
                break;
            }
        }
    }
}