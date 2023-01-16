#include <stdio.h>
#include <stdlib.h>
#define ordem 5
#define minimo 2

//Definindo o registro
struct aluno {
    char *nome;
    char *curso;
    int RA_UNESP;
};
typedef struct aluno aluno;

struct arvore {
    int nChaves;
    int chaves[ordem-1]; //vetor com as chaves
    struct arvore *filhos[ordem]; //vetor com os filhos das chaves
};
typedef struct arvore arvore;

//Funções de sistema
void Menu();
int Recebe(struct aluno *A);

//Funções da arvore
arvore *criaNo(int RA, arvore *filho);
void insereNo(int RA, int pos, arvore *no, arvore *filho);
void divideNo(int RA, int *pchaves, int pos, arvore *no, arvore *child, arvore **novo);
int atribuiValor(int RA, int *pchaves, arvore *no, arvore **filho);
void insere(int RA);
void busca(int RA, int *pos, arvore *noBusca);
