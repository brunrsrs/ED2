#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"

#define bool int
#define true 1
#define false 0
#define MAX 256

int main()  {
    int qtd_chars = 0; //tamanho do texto 
    int colunas = 1; //(pois deverá ter tamanho + 1)
    int qtd_bin = 0; //conta quantos digitos binarios terão

    char **dicionario; //onde será armazenado cada valor de char
    char *codificado; //texto codificado será armazenado

    unsigned int tab[MAX]; //tabela de frequencia
    inicializa_tab(tab); //inicializa ela com zeros

    lista *L = malloc(sizeof(lista));
    no *N, *arvore;

    FILE *leitor;
    FILE *compac;

    leitor = fopen("teste.txt", "r");

    //printf("O programa irá gerar um arquivo com texto codificado:\n");

    char aux;
    while (!feof(leitor)) { //pega os valores pra tabela
         aux = fgetc(leitor);
         tab[aux]++;
         qtd_chars++;
    }

    cria_lista(L);
    preenche_lista(L, tab);

    arvore = montar_arvore(L); //monta a arvore
    colunas += altura_arvore(arvore); //conta quantas colunas serão necessárias
    dicionario = memoria_dicionario(colunas); //aloca memoria para o dicionario
    gerar_dicionario(dicionario, arvore, "", colunas); //gera o dicionario baseado na arvore


    fclose(leitor);

return 0;
}