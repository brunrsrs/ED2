#include "atividade4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

arvore *raiz;

    //Funções
void Menu() {
    printf("\t\nO que deseja fazer?\n");
    printf("[1] - Gravar aluno\n");
    printf("[2] - Buscar aluno\n");
    printf("[3] - Fechar\n");
}

    //Função que recebe dados do aluno
int Recebe(struct aluno *a) {
    char nome[70];
    printf("Digite o nome do aluno: ");
    scanf(" %[^\n]c", nome);

    a->nome = (char*)malloc(sizeof(strlen(nome)+1));
    strcpy(a->nome, nome);

    char curso[70];
    printf("Digite o curso do aluno: ");
    scanf(" %[^\n]c", curso);

    a->curso = (char*)malloc(sizeof(strlen(curso)+1));
    strcpy(a->curso, curso);

    do {
    printf("Digite o RA do aluno: ");
    scanf(" %d", &a->RA_UNESP);
            /*RA sempre tem 9 numeros, portanto o minimo é o maior n° de 8 dígitos e o maximo
            é o maior n° de 9 dígitos*/
    if (a->RA_UNESP < 99999999 || a->RA_UNESP>999999999)
        printf("\tValor Inválido de RA\n\n");
    } while (a->RA_UNESP < 99999999 || a->RA_UNESP>999999999);

return 1;
}

    //funções da arvore
arvore *criaNo(int RA, arvore *filho) {
    struct arvore *novo;
    novo = (arvore *)malloc(sizeof(arvore));
    novo->chaves[1] = RA;
    novo->nChaves = 1;
    novo->filhos[0] = raiz;
    novo->filhos[1] = filho;
    return novo;
}

void insereNo(int RA, int pos, arvore *no, arvore *filho) {
    int j = no->nChaves;
    while (j > pos) {
        no->chaves[j + 1] = no->chaves[j];
        no->filhos[j + 1] = no->filhos[j];
        j--;
    }
    no->chaves[j + 1] = RA;
    no->filhos[j + 1] = filho;
    no->nChaves++;
}

void divideNo(int RA, int *pchaves, int pos, arvore *no, arvore *child, arvore **novo) {
    int meio, j;

    if (pos > minimo)
        meio = minimo + 1;
    else
        meio = minimo;

    *novo = (arvore *)malloc(sizeof(arvore));
    j = meio + 1;
    while (j <= ordem) {
        (*novo)->chaves[j - meio] = no->chaves[j];
        (*novo)->filhos[j - meio] = no->filhos[j];
        j++;
    }
    no->nChaves = meio;
    (*novo)->nChaves = ordem - meio;

    if (pos <= minimo)
        insereNo(RA, pos, no, child);
    else
        insereNo(RA, pos - meio, *novo, child);

    *pchaves = no->chaves[no->nChaves];
    (*novo)->filhos[0] = no->filhos[no->nChaves];
    no->nChaves--;
}

int atribuiValor(int RA, int *pchaves, arvore *no, arvore **filho) {
    int pos;
    if (!no) {
        *pchaves = RA;
        *filho = NULL;
        return 1;
    }

    if (RA < no->chaves[1])
        pos = 0;

    else {
        for (pos = no->nChaves;
        (RA < no->chaves[pos] && pos > 1); pos--);
        if (RA == no->chaves[pos]) {
            printf("Esse RA já foi inserido\n");
            return 0;
        }
    }
    
    if (atribuiValor(RA, pchaves, no->filhos[pos], filho)) {
        if (no->nChaves < ordem)
            insereNo(*pchaves, pos, no, *filho);

        else {
            divideNo(*pchaves, pchaves, pos, no, *filho, filho);
            return 1;
        }
    }
    return 0;
}

void insere(int RA) {
    int flag, i;
    arvore *filho;

    flag = atribuiValor(RA, &i, raiz, &filho);
    if (flag)
        raiz = criaNo(i, filho);
}

void busca(int RA, int *pos, arvore *noBusca) {
    if (!noBusca)
        return;

    if (RA < noBusca->chaves[1])
        *pos = 0;
    
    else {
        for (*pos = noBusca->nChaves;
        (RA < noBusca->chaves[*pos] && *pos > 1); (*pos)--);
        if (RA == noBusca->chaves[*pos]) {
        printf("%d foi encontrado", RA);
        return;
        }
    }
    busca(RA, pos, noBusca->filhos[*pos]);

    return;
}

void MostraPorNivel(arvore *no, int altura) {
    if (!no)
        return;

    for (int i=0; i<=altura; i++) {
        printf("\n\tNivel %d\n", i);
        BuscaNivel(no, altura, i);
        printf("\n");
    }
}
