#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ordem 5
#define minimo 2

FILE *arqDados, *arqIndice;

//Definindo o registro
typedef struct aluno {
  char *nome;
  char *curso;
  int RA_UNESP;
  int RNN;
}aluno;

typedef struct arvore {
  aluno chaves[ordem+1];
  int nChaves;
  struct arvore *filhos[ordem + 1];
}arvore;

  arvore *raiz;

void Menu() {
    printf("\t\nO que deseja fazer?\n");
    printf("[1] - Gravar aluno\n");
    printf("[2] - Buscar aluno\n");
    printf("[3] - Fechar\n");
}

    //Função que recebe dados do aluno
void Recebe(struct aluno *a) {
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
}

void armazenaArquivo(aluno *A) {
  int inicio, fim;
  fseek(arqDados, 0, SEEK_END);
  inicio = ftell(arqDados);
  fprintf(arqDados, "|%d|%s|%s|", A->RA_UNESP, A->nome, A->curso);
  fim = ftell(arqDados);
  for (int i=0; i<128-(fim-inicio); i++)
    fprintf(arqDados, "#");
  A->RNN = inicio; //salva o RNN para o arquivo de indice
}

void atualizaIndice() {
//  fprintf(arqIndice, "raiz: %d", )

}

// Create a no
arvore *criaNo(int chave, arvore *filho) {
    arvore *novo;
    novo = (arvore *)malloc(sizeof(arvore));
    novo->chaves[1].RA_UNESP = chave;
    novo->nChaves = 1;
    novo->filhos[0] = raiz;
    novo->filhos[1] = filho;
    return novo;
}

// insere no
void insereNo(int chaves, int pos, arvore *no,  arvore *filho) {
    int j = no->nChaves;
    while (j > pos) {
      no->chaves[j + 1] = no->chaves[j];
      no->filhos[j + 1] = no->filhos[j];
      j--;
    }
    no->chaves[j + 1].RA_UNESP = chaves;
    no->filhos[j + 1] = filho;
    no->nChaves++;
}

// Split no
void divideNo(int chaves, int *pchaves, int pos,  arvore *no,  arvore *filho,  arvore **novo) {
    int meio, j;

    if (pos > minimo)
      meio = minimo + 1;
    else
      meio = minimo;

    *novo = ( arvore *)malloc(sizeof( arvore));
    j = meio + 1;
    while (j <= ordem) {
      (*novo)->chaves[j - meio] = no->chaves[j];
      (*novo)->filhos[j - meio] = no->filhos[j];
      j++;
    }
    no->nChaves = meio;
    (*novo)->nChaves = ordem - meio;

    if (pos <= minimo) {
      insereNo(chaves, pos, no, filho);
    } else {
      insereNo(chaves, pos - meio, *novo, filho);
    }
    *pchaves = no->chaves[no->nChaves].RA_UNESP;
    (*novo)->filhos[0] = no->filhos[no->nChaves];
    no->nChaves--;
}

// Set the chavesue
int atribuiValor(int chaves, int *pchaves,  arvore *no,  arvore **filho) {
    int pos;
    if (!no) {
        *pchaves = chaves;
        *filho = NULL;
        return 1;
    }

    if (chaves < no->chaves[1].RA_UNESP)
        pos = 0;

    else {
        for (pos = no->nChaves;
        (chaves < no->chaves[pos].RA_UNESP && pos > 1); pos--);
        if (chaves == no->chaves[pos].RA_UNESP) {
        printf("Esse RA já foi inserido\n");
        return 0;
        }
    }

    if (atribuiValor(chaves, pchaves, no->filhos[pos], filho)) {
        if (no->nChaves < ordem)
            insereNo(*pchaves, pos, no, *filho);

        else {
            divideNo(*pchaves, pchaves, pos, no, *filho, filho);
            return 1;
        }
    }
    return 0;
}

// insere the chavesue
void insere(int chaves) {
  int flag, i;
    arvore *filho;

  flag = atribuiValor(chaves, &i, raiz, &filho);
  if (flag)
    raiz = criaNo(i, filho);
}

// Search no
void busca(int chaves, int *pos,  arvore *noBusca) {
    if (!noBusca)
        return;

    if (chaves < noBusca->chaves[1].RA_UNESP)
        *pos = 0;
    
    else {
        for (*pos = noBusca->nChaves;
        (chaves < noBusca->chaves[*pos].RA_UNESP && *pos > 1); (*pos)--);
        if (chaves == noBusca->chaves[*pos].RA_UNESP) {
        printf("%d foi encontrado", chaves);
        return;
        }
    }
    busca(chaves, pos, noBusca->filhos[*pos]);

    return;
}

void mostraTodos(arvore *no) {
  int i;
  if (no) {
    for (i = 0; i < no->nChaves; i++) {
      mostraTodos(no->filhos[i]);
      printf("%d ", no->chaves[i + 1].RA_UNESP);
    }
    mostraTodos(no->filhos[i]);
  }
}


////////////////////////////////////////////
//função main
int main() {
  int chaves, ch;
  int op=0;
  aluno A;

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
        Recebe(&A);
        armazenaArquivo(&A);
        insere(A.RA_UNESP);        

        fclose(arqIndice);
        arqIndice = fopen("ibtree.idx", "w");

        atualizaIndice(A);
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

fclose(arqDados);
fclose(arqIndice);

return 0;
}