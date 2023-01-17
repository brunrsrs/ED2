#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ordem 5
#define minimo 2

FILE *arqDados, *arqIndice;

////////////////////////////////////////////
//Definindo os registros
typedef struct aluno {
  char *nome;
  char *curso;
  int RA_UNESP;
  int RRN;
}aluno;

typedef struct arvore {
  aluno chaves[ordem+1];
  int nChaves;
  struct arvore *filhos[ordem + 1];
}arvore;

arvore *raiz = NULL;

////////////////////////////////////////////
//declarações
//funções de sistema
void Menu();
void Recebe(struct aluno *a);
void atualizaIndice(arvore *B);
void montaArvore(aluno no);
void armazenaArquivo(aluno *A);

//funções da arvore
arvore *criaNo(aluno chave, arvore *filho);
void insereNo(aluno chaves, int pos, arvore *no,  arvore *filho);
void divideNo(aluno chaves, aluno *pchaves, int pos,  arvore *no,  arvore *filho,  arvore **novo);
int atribuiValor(aluno chaves, aluno *pchaves,  arvore *no,  arvore **filho);
void insere(aluno chave);
void busca(int chaves, int *pos,  arvore *noBusca);
void mostraTodos(arvore *no);

////////////////////////////////////////////
//funções
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

void atualizaIndice(arvore *B) {
  int i;
  if (B) {
    for (i = 0; i < B->nChaves; i++) {
      atualizaIndice(B->filhos[i]);
      fprintf(arqIndice, "%d ", B->chaves[i + 1].RA_UNESP);
      fprintf(arqIndice, "%d\n", B->chaves[i + 1].RRN);
    }
    atualizaIndice(B->filhos[i]);
  }
}

void montaArvore(aluno no) {
  while (!feof(arqIndice)) {
    fscanf(arqIndice, "%d %d\n", &no.RA_UNESP, &no.RRN);
    insere(no);
  }
}

void armazenaArquivo(aluno *A) {
  int inicio, fim;
  fseek(arqDados, 0, SEEK_END);
  inicio = ftell(arqDados);
  fprintf(arqDados, "|%d|%s|%s|", A->RA_UNESP, A->nome, A->curso);
  fim = ftell(arqDados);
  for (int i=0; i<128-(fim-inicio); i++)
    fprintf(arqDados, "#");
  A->RRN = inicio; //salva o RRN para o arquivo de indice
}


arvore *criaNo(aluno chave, arvore *filho) {
    arvore *novo;
    novo = (arvore *)malloc(sizeof(arvore));
    novo->chaves[1].RA_UNESP = chave.RA_UNESP;
    novo->chaves[1].RRN = chave.RRN;
    novo->nChaves = 1;
    novo->filhos[0] = raiz;
    novo->filhos[1] = filho;
    return novo;
}

void insereNo(aluno chaves, int pos, arvore *no,  arvore *filho) {
    int j = no->nChaves;
    while (j > pos) {
      no->chaves[j + 1] = no->chaves[j];
      no->filhos[j + 1] = no->filhos[j];
      j--;
    }
    no->chaves[j + 1].RA_UNESP = chaves.RA_UNESP;
    no->chaves[j + 1].RRN = chaves.RRN;
    no->filhos[j + 1] = filho;
    no->nChaves++;
}

void divideNo(aluno chaves, aluno *pchaves, int pos,  arvore *no,  arvore *filho,  arvore **novo) {
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
      insereNo(chaves, pos, no, filho);

    else
      insereNo(chaves, pos - meio, *novo, filho);

    pchaves->RA_UNESP = no->chaves[no->nChaves].RA_UNESP;
    pchaves->RRN = no->chaves[no->nChaves].RRN;
    (*novo)->filhos[0] = no->filhos[no->nChaves];
    no->nChaves--;
}

int atribuiValor(aluno chaves, aluno *pchaves,  arvore *no,  arvore **filho) {
    int pos;
    if (!no) {
        *pchaves = chaves;
        *filho = NULL;
        return 1;
    }

    if (chaves.RA_UNESP < no->chaves[1].RA_UNESP)
        pos = 0;

    else {
        for (pos = no->nChaves;
        (chaves.RA_UNESP < no->chaves[pos].RA_UNESP && pos > 1); pos--);
        if (chaves.RA_UNESP == no->chaves[pos].RA_UNESP) {
        printf("\n\tAviso: esse RA já foi inserido\nInserindo mesmo assim");
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

void insere(aluno chave) {
  int flag;
  aluno i;
    arvore *filho;

  flag = atribuiValor(chave, &i, raiz, &filho);
  if (flag)
    raiz = criaNo(i, filho);
}

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
      printf("%d\n", no->chaves[i + 1].RRN);
    }
    mostraTodos(no->filhos[i]);
  }
}

int procuraItem(arvore *no, int val)
{
  int i;
  aluno a;
  if (no)
  {
    for (i = 0; i < no->nChaves; i++)
    {
      if (procuraItem(no->filhos[i], val))
        return 1;

      if (no->chaves[i + 1].RA_UNESP == val) {
        char c[1];
        fseek(arqDados, no->chaves[i+1].RRN + 1, SEEK_SET);
        fscanf(arqDados, "%d|", &a.RA_UNESP);

        a.nome = (char*)malloc(sizeof(70));
        c[0] = fgetc(arqDados);
        do {
          strcat(a.nome, c);
          c[0] = fgetc(arqDados);
        } while (c[0] != '|');
        fseek(arqIndice, 1, SEEK_CUR);

        a.curso = (char*)malloc(sizeof(70));
        c[0] = fgetc(arqDados);
        do {
          strcat(a.curso, c);
          c[0] = fgetc(arqDados);
        } while (c[0] != '|');

        printf("\n\tEncontrado!!\n");
        printf("%s - %s - %d\n", a.nome, a.curso, a.RA_UNESP);

        return 1;
      }
    }

    if (procuraItem(no->filhos[i], val))
      return 1;
  }

  return 0;
}

////////////////////////////////////////////
//função main
int main() {
  int chave, ch;
  int op=0;
  aluno A;

  arqDados = fopen("turma.dat", "r+");
  if (!arqDados)
      arqDados = fopen("turma.dat", "w+");

  arqIndice = fopen("ibtree.idx", "r+");
  if (!arqIndice)
    arqIndice = fopen("ibtree.idx", "w+");
    
  else
    montaArvore(A);

  fseek(arqIndice, 0, SEEK_SET);

do {
    Menu();
    printf("Comando: ");
    scanf(" %d", &op);

    switch(op) {
      case 1:
        Recebe(&A);
        armazenaArquivo(&A);
        insere(A);        
      break;

      case 2:
        printf("Digite o RA que deseja buscar: ");
        scanf(" %d", &chave);
        if (!procuraItem(raiz, chave))
          printf("\n\tValor não encontrado");
      break;

      case 3:
      break;

      default:
        printf("\n\tValor inválido\n");
      break;
    }
} while(op!=3);

fseek(arqIndice, 0, SEEK_SET);
atualizaIndice(raiz);

fclose(arqDados);
fclose(arqIndice);

return 0;
}