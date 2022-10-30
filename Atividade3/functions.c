#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define bool int
#define true 1
#define false 0
#define MAX 256

//inicializa o vetor de elementos
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
void preenche_lista(lista *L, unsigned int t[]) {
    no *novo;

    for (int i=0; i<MAX; i++) {
        if (t[i] > 0) { //se o char aparecer no texto

            novo = malloc(sizeof(no));
            if (novo) {
                novo->dir = NULL;
                novo->prox = NULL;
                novo->esq = NULL;
                novo->valor.letra = i;
                novo->valor.peso = t[i];

                insere_ordenado(L, novo); //insere ordenadamente na lista
            }
            else {
                printf("Não foi possivel alocar memoria");
                break;
            }
        }
    }
}

//insere na lista
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
        L->raiz = N;
        L->tam++;
    }

    //inserir no meio/fim
    else {
        aux = L->raiz;
        while (aux->prox!=NULL && aux->prox->valor.peso <= N->valor.peso)
            aux = aux->prox;

        N->prox = aux->prox;
        aux->prox = N;
        L->tam++;
    }
}


//função pra testar a ordem da lista
void imprimir_lista(lista *L) {
    no *aux = L->raiz;
    printf("\tLista ordenada: Tamanho: %d\n", L->tam);

    while(aux) {
        printf("\tCaracter: %c Frequencia: %d\n", aux->valor.letra, aux->valor.peso);
        aux = aux->prox;
    }
}


//operação para montar arvore --------------
no* remove_elem (lista *L) {
    no *aux;
    aux = NULL;

    if(L->raiz){
        aux = L->raiz;
        L->raiz = aux->prox;
        aux->prox = NULL;
        L->tam--;
    }
    return aux;
}

no *montar_arvore(lista *L) {
    no *primeiro, *segundo, *novo;
    
    while(L->tam > 1){
        primeiro = remove_elem(L); //retorna o 1° elemento
        segundo = remove_elem(L); //retorna o 2° elemento
        novo = malloc(sizeof(no));
        novo->valor.letra = '+';
        novo->valor.peso = primeiro->valor.peso + segundo->valor.peso;
        novo->esq = primeiro; //primeiro é menor que o segundo pois está em ordem
        novo->dir = segundo;
        novo->prox = NULL;

        insere_ordenado(L, novo); //insere o nó na lista
    }
    return L->raiz;
}

void imprimir_arvore(no *raiz, int tam){ //mostra as folhas da arvore em ordem

    if(raiz->esq == NULL && raiz->dir == NULL)
        printf("\tFolha: %c\tAltura: %d\tPeso: %d\n", raiz->valor.letra, tam, raiz->valor.peso);

    else{
        imprimir_arvore(raiz->esq, tam+1);
        imprimir_arvore(raiz->dir, tam+1);
    }
}
