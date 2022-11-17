#include <stdio.h>
#include <stdlib.h>
#define MAX 3
#define MIN 2

//structs
typedef struct No {
    int item[MAX + 1], count;
    struct No *link[MAX + 1];
} No;

No *raiz;

//header
void inserir(int item);
int setNo(int item, int *pval, No *no, No **filho);
No *criarNo(int item, No *filho);
void InserirValor(int item, int pos, No *no,No *filho);
void divideNo(int item, int *pval, int pos, No *no, No *filho, No **novoNo);
void procura(No *noSelecionado);
int procuraIten(int item, No *no, int flag);

//Se a arvore estiver vazia, alocar o Nó raiz e inserir a chave
void inserir(int item) {
    int flag, i;
    No *filho;
    flag = setNo(item, &i, raiz, &filho);
    if (flag)
        raiz = criarNo(i, filho);
}

//Se o nó está cheio, realizar a divisão do nó
int setNo(int item, int *pval, No *no, No **filho) {
    int pos;
    if (!no) {
        *pval = item;
    *filho = NULL;
    return 1;
    }
    
    if (item < no->item[1]) {
    pos = 0;
    } 
    else {
        for (pos=no->count; (item < no->item[pos] && pos > 1); pos--);
            if (item == no->item[pos]) {
                printf("\n\tNão permite valor duplicado\n");
                return 0;
            }
    }

    if (setNo(item, pval, no->link[pos], filho)) {
        if (no->count < MAX) {
            InserirValor(*pval, pos, no, *filho);
            return 1;
        } 
        
        else {
            divideNo(*pval, pval, pos, no, *filho, filho);
            return 1;
        }
    }

return 0;
}

No *criarNo(int item, No *filho) {
    No *novoNo;
    novoNo = (No*)malloc(sizeof(No));
    novoNo->item[1] = item;
    novoNo->count = 1;
    novoNo->link[0] = raiz;
    novoNo->link[1] = filho;
    return novoNo;
}

//Pesquise o nó apropriado para inserção
//Atualize o número permitido de chaves no nó
void InserirValor(int item, int pos, No *no,No *filho) {
    int j = no->count;
    while (j > pos) {
        no->item[j + 1] = no->item[j];
        no->link[j + 1] = no->link[j];
        j--;
    }
    no->item[j + 1] = item;
    no->link[j + 1] = filho;
    no->count++;
}

//Se o nó estiver completo
void divideNo(int item, int *pval, int pos, No *no, No *filho, No **novoNo) {
    int mediana, j;
    if (pos > MIN)
        mediana = MIN + 1;
    else
        mediana = MIN;

    *novoNo = ( No *)malloc(sizeof( No));
    j = mediana + 1;
    while (j <= MAX) {
        (*novoNo)->item[j - mediana] = no->item[j];
        (*novoNo)->link[j - mediana] = no->link[j];
        j++;
    }
    no->count = mediana;
    (*novoNo)->count = MAX - mediana;
    if (pos <= MIN)
        InserirValor(item, pos, no, filho);

    else
    InserirValor(item, pos - mediana, *novoNo, filho);

    *pval = no->item[no->count];
    (*novoNo)->link[0] = no->link[no->count];
    no->count--;
    }


void procura(No *noSelecionado) {
    int i;
    if (noSelecionado) {
        for (i = 0; i < noSelecionado->count; i++) {
            procura(noSelecionado->link[i]);
            printf("%d ", noSelecionado->item[i + 1]);
        }
        procura(noSelecionado->link[i]);
    }
}

int procuraIten(int item, No *no, int flag) {
    int pos;
    
    for (pos = 0; pos<no->count; pos++)
        if (no->item[pos] == item)
            flag = 1;

    if (flag == 0) {
        for (pos=0; pos<no->count; pos++)
            procuraIten(item, no->link[pos], flag);
    }

if (flag == 1)
    return 1;

else
    return 0;
}

int main() {
    int item, cmd = 0;

    do {
        printf("\n\tDigite o que deseja fazer:\n");
        printf("[1] - Inserir\n[2] - Localizar\n[3] - Sair\nComando: ");
        scanf(" %d", &cmd);

        switch (cmd) {
            case 1:
                printf("Digite o valor: ");
                scanf(" %d", &item);

                inserir(item);
            break;

            case 2:
                printf("Digite o valor: ");
                scanf(" %d", &item);

                if (procuraIten(item, raiz, 0) == 1)
                    printf("\n\tValor encontrado\n");
                else
                    printf("\n\tValor não encontrado\n");

            break;

            case 3:
            break;

            default:
                printf("\n\tValor inválido\n");
        }


    } while (cmd != 3);

return 0;
}