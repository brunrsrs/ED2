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
    int chaves[ordem-1]; //vetor com as chaves
    struct arvore *filhos[ordem]; //vetor com os filhos das chaves
};
typedef struct arvore tree, arvore;

//Funções do programa passado
void Menu();
int Recebe(struct aluno *A);
int BuscaRA(int *desloc);

//funções a se criar:
void mostrarDados(int RRN);
int buscarArqDados(int RA); //função pra procurar no ibtree.idx o RNN de tal chave
//int gravarAluno();
//aluno buscarAluno 

//funções da arvore B a se criar
int criaArvB(arvore *B);
int buscaNaArv(arvore *B, int RA, int *i);
int buscaNaChave(int tam, arvore B, int chave);
//void inserirArvB();
//int buscarArvB();
//void printArvB