#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

#define MAX 256

//funções gerais ------------------

//exibe o que o usuario pode fazer
void selecao() {
    printf("\nO que deseja fazer?:");
    printf("\n\t[1] - compactar arquivo\n\t[2] - descompactar arquivo\n\t[3] - sair\ncomando: ");
}

//inicializa o vetor de elementos
void inicializa_tab(unsigned int t[]) {
    for (int i=0; i<MAX; i++) {
        t[i] = 0;
    }
}

void mostra_texto(char *t, int size) {
    for (int i=0; i<size-1; i++)
        printf("%c", t[i]);

    printf("\n");
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

    dicionario = malloc(sizeof(char*) * MAX); //cria 256 linhas

    for(int i = 0; i < MAX; i++) { //para todas as linhas, cria as colunas
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
    for(int i = 0; i < MAX; i++){
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
    return tam;
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

//calcula a qtd de numeros em binario
int tam_string_bin(char *texto) {
    int qtd=0;

    while (texto[qtd]!='\0')
        qtd++;

    return qtd;
}

//funções de conversão -----------

//compacta o texto binario
char convert_byte (char *vet , int n) { 
    char rtno = 0, i = 0; 
    
    while (i<n) {
        rtno += pow(2.0, (double)i) * (vet[n-1-i] - 48);
        i++; 
    }

    return rtno ; 
} 

void convert (char ch, char *Vet) {
    int i = 7; //indice auxiliar

    while (i>=0) {
        if (ch & 1)
            Vet [i] = '1';
        else
            Vet [i] = '0';

        i--;
        ch >>= 1;
    }
}

//função que decodifica o texto de binario para o normal
char* decodificar(unsigned char texto[], no *raiz){
    int i = 0;
    no *aux = raiz;
    char temp[2];
    char *decodificado = calloc(strlen(texto), sizeof(char));

    while(texto[i] != '\0'){
        if(texto[i] == '0')
            aux = aux->esq; 
        else
            aux = aux->dir;

        //se for um nó folha concatena o caracter e volta para a raiz da árvore
        if(aux->esq == NULL && aux->dir == NULL){
            temp[0] = aux->letra;
            temp[1] = '\0';
            strcat(decodificado, temp);
            aux = raiz;
        }
        i++;
    }
    
    return decodificado;
}

//função para calcular tamanho ------------
int calcula_bits(unsigned int tab[], char** dicionario) {
    int tam_original = 0;
    int tam_comprimido = 0;

    for (int i=0; i<MAX; i++)
        if (tab[i] != 0) {
            tam_original += 8 * tab[i];
            tam_comprimido += strlen(dicionario[i]);
        }

    return tam_original - tam_comprimido;
}