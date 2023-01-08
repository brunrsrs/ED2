#include "atividade4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool int
#define TRUE 1
#define FALSE 0

//Funções
void Menu() {
    printf("\t\nO que deseja fazer?\n");
    printf("[1] - Gravar aluno\n");
    printf("[2] - Buscar aluno\n");
    printf("[3] - Fechar\n");
}

int gravarAluno() {
    
}







//Função que recebe? nao sei nao lembro oq eu fiz pq n comentei nada
bool Recebe(struct aluno *a) {
    char nome[50];
    printf("Digite o RA do aluno: ");
    scanf(" %[^\n]c", nome);

    a->nome = (char*)malloc(sizeof(strlen(nome)+1));
    strcpy(a->nome, nome);

    char curso[50];
    printf("Digite o curso do aluno: ");
    scanf(" %[^\n]c", curso);

    a->curso = (char*)malloc(sizeof(strlen(curso)+1));
    strcpy(a->curso, curso);

    //Fazer verificação se não há igual
    do {
    printf("Digite o RA do aluno: ");
    scanf(" %d", &a->RA_UNESP);
            /*RA sempre tem 9 numeros, portanto o minimo é o maior n° de 8 dígitos e o maximo
            é o maior n° de 9 dígitos*/
    if (a->RA_UNESP < 99999999 || a->RA_UNESP>999999999)
        printf("\tValor Inválido de RA\n\n");
    } while (a->RA_UNESP < 99999999 || a->RA_UNESP>999999999);

return TRUE;
}

//Função que busca?
bool buscaRA(int *desloc) {
FILE *arqIndice;
int RA, num;
    do {
    printf("\nDigite o RA de que deseja encontrar: ");
    scanf(" %d", &RA);
    if (RA < 99999999 || RA>999999999)
        printf("\tRA Inválido\n");
    } while(RA < 99999999 || RA>999999999);

    arqIndice = fopen("index.txt", "r");
    if (!arqIndice) 
        return FALSE;

    while (!feof(arqIndice) && num != RA) {
        fscanf(arqIndice, "%d %d\n", &num, desloc);
    }

    if (num != RA)
        return FALSE;

return TRUE;
}