#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atividade4.c"

int main() {
int op=0;
int RA;
FILE *arqDados, *arqIndice;

aluno *A = malloc(sizeof(aluno));
arvore *B;
if (criaArvB(B) == 0)
    return 0;

    arqDados = fopen("turma.dat", "r+");
    if (!arqDados)
        arqDados = fopen("turma.dat", "w+");

    arqIndice = fopen("ibtree.idx", "r+");
    if (!arqIndice)
        arqIndice = fopen("ibtree.idx", "w+");

do {
    Menu();
    printf("Comando: ");
    scanf(" %d", &op);


    switch(op) {
        case 1:
            recebe(A);
        break;

        case 2:
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