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

    char *texto; //armazenará o arquivo de texto;
    char **dicionario; //onde será armazenado cada valor de char
    char *codificado; //texto codificado será armazenado

    unsigned int tab[MAX]; //tabela de frequencia
    inicializa_tab(tab); //inicializa ela com zeros

    lista *L = malloc(sizeof(lista));
    no *N, *arvore;

    FILE *leitor;
    FILE *compac;

    leitor = fopen("teste.txt", "r");
    if (!leitor) {
        printf("Não foi possivel abrir");
        return 0;
    }

    //printf("O programa irá gerar um arquivo com texto codificado:\n");

    char aux;
    while (!feof(leitor)) { //pega os valores pra tabela
         aux = fgetc(leitor);
         tab[aux]++;
         qtd_chars++;
    }

    texto = malloc((qtd_chars+1)*sizeof(char)); //aloca memoria pro texto

    int count=0;
    fseek(leitor, 0, SEEK_SET);
    while (!feof(leitor)) { //passa o texto para uma string
        aux = fgetc(leitor);
        texto[count] = aux;
        count++;
    }
    texto[qtd_chars+1] = '\0'; //coloca o operador para encerrar
    fclose(leitor);

    cria_lista(L);
    preenche_lista(L, tab);

    arvore = montar_arvore(L); //monta a arvore
    colunas += altura_arvore(arvore); //conta quantas colunas serão necessárias
    dicionario = memoria_dicionario(colunas); //aloca memoria para o dicionario
    gerar_dicionario(dicionario, arvore, "", colunas); //gera o dicionario baseado na arvore

    //variavel qtd_chars nao precisará mais acumular valores do texto inicial
    qtd_chars = calcula_tamanho_string(dicionario, texto);
    codificado = calloc(qtd_chars, sizeof(char));
    codificado = codificar(dicionario, texto);

    FILE *saida;
    saida = fopen("saida.txt", "w");
    for (int i=0; i<qtd_chars; i++) {
        fputc(codificado[i], saida);
    }
    fclose(saida);


return 0;
}