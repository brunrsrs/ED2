#include <stdio.h>
#include <stdlib.h>
#define ordem 5

//Definindo o registro
struct aluno {
    char *nome;
    char *curso;
    int RA_UNESP;

};
typedef struct aluno aluno;

struct arvore {
    int eFolha; //verifica se é folha (não da pra usar "é" nem "?" pra variavel)
    int nChaves; //conta quantas chaves tem
    aluno chaves[ordem-1]; //vetor com as chaves
    struct arvore *filhos[ordem]; //vetor com os filhos das chaves
};
typedef struct arvore tree, arvore;

//Funções do programa passado
void Menu();
int Recebe(struct aluno *A);
int BuscaRA(int *desloc);

//funções a se criar:
//int gravarAluno();
//aluno buscarAluno 

//funções da arvore B a se criar
int criaArvB(arvore *B);
//void inserirArvB();
//int buscarArvB();
//void printArvB