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
    no *novo = NULL;

    for (int i=0; i<MAX; i++) {
        if (t[i] > 0) { //se o char aparecer no texto

            novo = malloc(sizeof(no));
            if (novo) {
                novo->dir = NULL;
                novo->prox = NULL;
                novo->esq = NULL;
                novo->letra = i;
                novo->peso = t[i];

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
    else if (N->peso < L->raiz->peso) {
        N->prox = L->raiz;
        L->raiz = N;
        L->tam++;
    }

    //inserir no meio/fim
    else {
        aux = L->raiz;
        while (aux->prox!=NULL && aux->prox->peso <= N->peso)
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
        printf("\tCaracter: %c Frequencia: %d\n", aux->letra, aux->peso);
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

//organiza a arvore e as folhas
no *montar_arvore(lista *L) {
    no *primeiro, *segundo, *novo;
    
    while(L->tam > 1){ //sobrar apenas 1 elemento
        primeiro = remove_elem(L); //retorna o 1° elemento
        segundo = remove_elem(L); //retorna o 2° elemento
        novo = malloc(sizeof(no));
        novo->letra = '+';
        novo->peso = primeiro->peso + segundo->peso;
        novo->esq = primeiro; //primeiro é menor que o segundo pois está em ordem
        novo->dir = segundo;
        novo->prox = NULL;

        insere_ordenado(L, novo); //insere o nó na lista
    }
    return L->raiz;
}

//função pra testar a arvore
void imprimir_arvore(no *raiz, int tam){ //mostra as folhas da arvore em ordem

    if(raiz->esq == NULL && raiz->dir == NULL)
        printf("\tFolha: %c\tAltura: %d\tPeso: %d\n", raiz->letra, tam, raiz->peso);

    else{
        imprimir_arvore(raiz->esq, tam+1);
        imprimir_arvore(raiz->dir, tam+1);
    }
}

//funções para salvar as variaveis (dicionario) ---------
//aloca memoria do dicionario
char** memoria_dicionario(int colunas){
    char **dicionario;

    dicionario = malloc(sizeof(char*) * tam);

    for(int i = 0; i < tam; i++) {
        dicionario[i] = malloc(colunas*sizeof(char));
        for (int j=0; j<colunas; j++) //inicializa colunas com 0                                         
            dicionario[i][j] = 0;
    }

    return dicionario;
}