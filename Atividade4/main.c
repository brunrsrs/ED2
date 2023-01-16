#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atividade4.c"

int main() {
int op=0;
int RA;
FILE *arqDados, *arqIndice;

aluno *A = malloc(sizeof(aluno));
arvore *B = malloc(sizeof(arvore));
B->nChaves=0;
//raiz->nChaves=0;

    arqDados = fopen("turma.dat", "r+");
    if (!arqDados)
        arqDados = fopen("turma.dat", "w+");

    arqIndice = fopen("ibtree.idx", "r+");
    if (!arqIndice)
        arqIndice = fopen("ibtree.idx", "w+");


    //valores genericos de RA pra testar se ta inserindo função
  insere(8);
  insere(9);
  insere(10);
  insere(11);
  insere(15);
  insere(16);
  insere(17);
  insere(18);
  insere(20);
  insere(23);

do {
    Menu();
    printf("Comando: ");
    scanf(" %d", &op);

    switch(op) {
        case 1:
            Recebe(A);
            insere(A->RA_UNESP);
        break;

        case 2:
            mostraTodos(raiz);
        break;

        case 3:
        break;

        default:
            printf("\n\tValor inválido\n");
        break;
    }


} while(op!=3);


return 0;
}