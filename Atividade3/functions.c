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
    no *novo;

    for (int i=0; i<MAX; i++)
        if (t[i] > 0)
            printf("%c %d\n", i, t[i]);

    printf("\n");

    for (int i=0; i<MAX; i++) {
        if (t[i] > 0) {
            printf("%c %d\n", i, t[i]);

            novo = malloc(sizeof(no));
            if (novo) {
                novo->dir = NULL;
                novo->prox = NULL;
                novo->esq = NULL;
                novo->valor.letra = i;
                novo->valor.peso = t[i];


                //testando
                //printf("\npeso = %d\nchar = %c\n", novo->valor.peso, novo->valor.letra);

                insere_ordenado(L, novo);
            }
            else {
                printf("Não foi possivel alocar memoria");
                break;
            }
        }
    }
}

//insere na arvore
void insere_ordenado(lista *L, no *N) {
    no *aux;

    //caso a lista esteja vazia
    if (L->raiz == NULL) {
        L->raiz = N;
        L->tam++;
    }

    //inserir no inicio
    else if (N->valor.peso < L->raiz->valor.peso) {
        N->prox = L->raiz;
        L->raiz->prox = NULL;
        L->raiz = N;
        L->tam++;
    }

    else {
        aux = L->raiz;
        while (aux->prox!=NULL && aux->prox->valor.peso <= N->valor.peso)
            aux = aux->prox;
    
        N->prox = aux->prox;
        aux->prox = N;
        L->tam++;
    }

    //teste
    //printf(" no: %d, %c\n", N->valor.peso, N->valor.letra);
}