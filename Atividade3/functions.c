#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


//funções para montar a lista ---------

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
                printf("Não foi possivel alocar memória");
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

//retorna o elemento da lista
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

//operação para montar arvore --------------

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

//Mostra tamanho da arvore de huffman
int altura_arvore(no *raiz){
    int esq, dir;

    if(!raiz)
        return -1;

    else {
        esq = altura_arvore(raiz->esq) + 1;
        dir = altura_arvore(raiz->dir) + 1;

        if(esq > dir)
            return esq;
        else
            return dir;
    }
}

//aloca memoria do dicionario
char** memoria_dicionario(int colunas){
    char **dicionario;

    dicionario = malloc(sizeof(char*) * 256); //cria 256 linhas

    for(int i = 0; i < 256; i++) { //para todas as linhas, cria as colunas
        dicionario[i] = malloc(colunas*sizeof(char));
        for (int j=0; j<colunas; j++) //inicializa colunas com 0                                         
            dicionario[i][j] = 0;
    }

    return dicionario;
}

//função que gera os valores do dicionario
void gerar_dicionario(char **dicionario, no *raiz, char *caminho, int colunas) {
    char esquerda[colunas], direita[colunas];


    if(raiz->esq == NULL && raiz->dir == NULL)
        strcpy(dicionario[raiz->letra], caminho); //insere o caminho no vetor


    else {
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0"); //concatena os valores aos vetores
        strcat(direita, "1");

        gerar_dicionario(dicionario, raiz->esq, esquerda, colunas);
        gerar_dicionario(dicionario, raiz->dir, direita, colunas);
    }
}

//função de teste para mostrar o dicionario
void imprime_dicionario(char **dicionario){

    printf("\n\tDicionario:\n");
    for(int i = 0; i < 256; i++){
        if(strlen(dicionario[i]) > 0) //caso nao esteja vazio o vetor
            printf("\t%c: %s\n", i, dicionario[i]);
    }
}

//funções para trabalhar com o texto codificado ---------

//retorna o tamanho do texto codificado
int calcula_tamanho_string(char **dicionario, unsigned char *texto){
    int i = 0, tam = 0;
    while(texto[i] != '\0'){
        tam += strlen(dicionario[texto[i]]);
        i++;
    }
    return tam + 1;
}

//faz a codificação
char* codificar(char **dicionario, unsigned char *texto){

    int i = 0;
    int tam = calcula_tamanho_string(dicionario, texto);
    char *codificado = calloc(tam, sizeof(char));

    while(texto[i] != '\0'){
        strcat(codificado, dicionario[texto[i]]);
        i++;
    }
    return codificado;
}