#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

#define MAX 5
#define MIN 1

//structs
typedef struct No {
    int item[MAX + 1], count;
    struct No *link[MAX + 1];
} No, ArvB, NoArvB;

No *raiz;

//header
void inserir(int item);
int setNo(int item, int *pval, No *no, No **filho);
No *criarNo(int item, No *filho);
void InserirValor(int item, int pos, No *no,No *filho);
void divideNo(int item, int *pval, int pos, No *no, No *filho, No **novoNo);
void procura(No *noSelecionado);
void procuraIten(int item, No *no, int *posi, int *flag);

//remoção
void procuraIten(int item, No *no, int *posi, int *flag);
bool RemoveArvBRec(NoArvB **no, int chave, bool *underflow);
bool BuscaChaveNoArvB(NoArvB *no, int chave, int *pos);
bool RemoveArvBRec(NoArvB **no, int chave, bool *underflow);
void TrocaChaveComAntecessora(NoArvB *no, int pos);
void TrataNoComMenosChavesQuePermitido(NoArvB **no, int pos);
void RemoveChaveEmNo(NoArvB *no, int pos);
bool NoComMaisChavesQuePossivel(NoArvB *no);
bool NoComMenosChavesQuePermitido(NoArvB *no);

//Se a arvore estiver vazia, alocar o Nó raiz e inserir a chave
void inserir(int item) {
    int flag, i;
    No *filho;
    flag = setNo(item, &i, raiz, &filho);
    if (flag)
        raiz = criarNo(i, filho);
}

//Se o nó está cheio, realizar a divisão do nó
int setNo(int item, int *pval, No *no, No **filho)
{
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
            printf("Não permite valor duplicado\n");
            return 0;
        }
    }

    if (setNo(item, pval, no->link[pos], filho)) {
        if (no->count < MAX) {
            InserirValor(*pval, pos, no, *filho);
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

    *novoNo = (No *)malloc(sizeof(No));
    j = mediana + 1;
    while (j <= MAX) {
        (*novoNo)->item[j - mediana] = no->item[j];
        (*novoNo)->link[j - mediana] = no->link[j];
        j++;
    }
    no->count = mediana;
    (*novoNo)->count = MAX - mediana;
    if (pos <= MIN)
    {
        InserirValor(item, pos, no, filho);
    } 
    else {
        InserirValor(item, pos - mediana, *novoNo, filho);
    }
    *pval = no->item[no->count];
    (*novoNo)->link[0] = no->link[no->count];
    no->count--;
}


void procura( No *noSelecionado) {
    int i;
    if (noSelecionado) {
        for (i = 0; i < noSelecionado->count; i++) {
            procura(noSelecionado->link[i]);
            printf("%d ", noSelecionado->item[i + 1]);
        }
        procura(noSelecionado->link[i]);
    }
}

void procuraIten(int item, No *no, int *posi, int *flag) {
    if(!no)
        return;

    if (item < no->item[1])
        *posi=0;
    else {
        for(*posi = no->count; item<no->item[*posi] && *posi>1; *posi--);
        if (item == no->item[*posi]) {
            *flag = 1;
            return;
        }
    }
    procuraIten(item, no->link[*posi], posi, flag);
    return;
}

//remoção
bool RemoveArvB(ArvB **arvore, int chave)
{
  if ((*arvore) == NULL){
    printf("Erro em RemoveArvB: Árvore inexistente\n");
    exit(1);
  }
  bool underflow=false;
  
  if(RemoveArvBRec(arvore, chave, &underflow)){ /* A chave foi removida */

    /* Se o underflow chegou até a raiz da arvore, entao a raiz antiga
       deve ser eliminada e a nova será a sua única link, reduzindo
       assim a altura da arvore em 1.
    */
    
    if(underflow) {
      NoArvB *no = *arvore;
      *arvore = (*arvore)->link[0];
      free(no);
    }
    return(true);
  }
  return(false);
}

bool RemoveArvBRec(NoArvB **no, int chave, bool *underflow)
{
  int pos;
  
  /* Verifica se a chave está no nó atual. Se tiver e esse nó for uma
  folha, realiza a remoção. Caso contrário, troca a chave pela
  antecessora e continua o procedimento recursivo para remoção. */

  if (BuscaChaveNoArvB(*no, chave, &pos)) {     /* a chave está no nó deste nível */
     if ((*no)->link[pos]!=NULL) {    
            /* O nó atual não é uma folha,
			 		  então a chave precisa ser trocada pela antecessora, reduzindo ao caso de remoção na folha. */

          TrocaChaveComAntecessora(*no, pos);   /* troca a chave pela sua antecessora -- i.e., a
					       chave mais à direita na árvore à esquerda. continua o procedimento recursivo para
                 reencontrar e remover a chave do nó folha */

          RemoveArvBRec(&((*no)->link[pos]), chave, underflow);
          /* trata underflow, se for o caso, após a remoção da chave */
          if (*underflow) 
             TrataNoComMenosChavesQuePermitido(no, pos); 

     } else { /* achou a chave no nó folha, então ela pode ser removida. */
        RemoveChaveEmNo(*no, pos);
     }
     /* verifica se a folha ficou em underflow */

     (*underflow) = NoComMenosChavesQuePermitido(*no); 
     return(true);   /* remoção bem sucedida */
  } else { /* procura a chave nos nós abaixo */
     if ((*no)->link[pos] != NULL) {
        if (RemoveArvBRec(&((*no)->link[pos]), chave, underflow)) {
	            /* a chave foi encontrada e removida da folha (raiz da árvore
	            link). Trata um possível underflow e verifica novamente se
	            ele será propagado para cima (volta da recursão). */
	          if (*underflow)
               TrataNoComMenosChavesQuePermitido(no, pos);
	          (*underflow) = NoComMenosChavesQuePermitido(*no);
	          return(true);
        } else {
	          return(false); /* chego na folha e não achou a chave */
        }
     } else {  /* estamos na raiz e a chave não está neste nível, logo ela não existe. */
        (*underflow) = false;
         return(false);
     }
  }
}

bool BuscaChaveNoArvB(NoArvB *no, int chave, int *pos)
{
  for ((*pos)=0; (no->item[*pos] < chave) && (*pos) < no->count; (*pos)++);

  /* "pos" contém a posição da chave no nó */
  if (((*pos) < no->count)&&(no->item[*pos] == chave))
     return(true);

  /* "pos" contém a posição da árvore link na qual a chave poderá ser encontrada */
  return(false);
}


void TrocaChaveComAntecessora(NoArvB *no, int pos)
{
  ArvB *no_aux;
  int   chave_aux;
  
  no_aux = no->link[pos]; /* árvore link à esquerda da chave na posição "pos" */
  while(no_aux->link[no_aux->count]!=NULL) /* busca a chave mais à direira na àrvore esquerda (i.e., a antecessora da chave que está em "no" na posição "pos") */
      no_aux = no_aux->link[no_aux->count];

  /* troca a chave por sua antecessora na árvore B */
  chave_aux  = no->item[pos];
  no->item[pos] = no_aux->item[no_aux->count-1];
  no_aux->item[no_aux->count-1] = chave_aux;
}

void TrataNoComMenosChavesQuePermitido(NoArvB **no, int pos)
{
  int chave,i,j;
  NoArvB *irma_esq=NULL, *link=NULL, *irma_dir=NULL;

  link = (*no)->link[pos];
  
  if (pos > 0) { /* existe irmã à esquerda da link */ 
     irma_esq = (*no)->link[pos-1];
    //if(irma_esq->count > (((*no)->ordem)/2)) { 
                          /* A irmã à esquerda tem chaves para emprestar. A sua última chave sobe
						  para o nó pai e a chave do nó pai  desce para a link na posição mais à esquerda. A link à direira da chave que
						  subiu passa a ser link à esquerda daquela que desceu.*/
    if(irma_esq->count > MAX/2) {   
         chave = (*no)->item[pos-1];    
         (*no)->item[pos-1]=irma_esq->item[irma_esq->count-1]; 
         NoArvB *link_esq          = irma_esq->link[irma_esq->count]; 
         RemoveChaveEmNo((*no)->link[pos-1],(*no)->link[pos-1]->count);
         link->count++;
         link->link[0] = link_esq;
         link->item[0] = chave;
         return;
     }
  }
  
  if (pos < (*no)->count) { /* existe irmã à direita */ 
    irma_dir = (*no)->link[pos+1];
    //if (irma_dir->count > (((*no)->ordem)/2)) { 
                          /* A irmã à direita tem chaves para
						  emprestar. A sua primeira chave sobe para o nó pai e a chave do nó pai desce para a link na posição mais à
						  direita. A link à esquerda da chave que subiu passa a ser link à direita daquela que desceu. */
    if (irma_dir->count > MAX/2) {   
        chave   = (*no)->item[pos];
        (*no)->item[pos] = irma_dir->item[0];
        NoArvB *link_dir = irma_dir->link[0];
        RemoveChaveEmNo((*no)->link[pos+1],0);
        link->count++;
        link->link[link->count]   = link_dir;
        link->item[link->count-1] = chave;
        return;
    }    
  }
}

void RemoveChaveEmNo(NoArvB *no, int pos)
{
  int i;
  /* desloca as chaves e links para trás */
  for(i=pos; i < no->count; i++)
  {
      no->item[i] = no->item[i+1];
      no->link[i] = no->link[i+1];
  }
  /* completa o deslocamento para a link à direita da última chave */ 
  no->link[i]   = no->link[i+1];
  no->link[i+1] = NULL;
  /* ajusta o número de registros */
  no->count--;
}

bool NoComMaisChavesQuePossivel(NoArvB *no)
{
  //return(no->count > no->ordem);
  return(no->count > MAX);

}

bool NoComMenosChavesQuePermitido(NoArvB *no)
{
  //return(no->count < (no->ordem/2));
  return(no->count < MAX/2);
}



int main() {
    int item, posi, cmd = 0, flag = 0;

    do {
        printf("\n\tDigite o que deseja fazer:\n");
        printf("[1] - Inserir\n[2] - Localizar\n[3] - Remover item\n[0] - Sair\nComando: ");
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

//                flag=0;
//                procuraIten(item, raiz, 0, &flag);

                printf("\n\tRaiz completa:\n");
                procura(raiz);

                if (BuscaChaveNoArvB(raiz, item, &posi))
                    printf("\n\tValor encontrado!!\n");
                else
                    printf("\n\tValor não encontrado!\n");
            break;

            case 3:
                printf("Digite o valor: ");
                scanf(" %d", &item);

                RemoveArvB(&raiz, item);
            break;

            case 0:
            break;

            default:
                printf("\n\tValor inválido\n");
        }


    } while (cmd != 0);

return 0;
}