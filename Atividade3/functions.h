#define bool int
#define true 1
#define false 0
#define MAX 256

typedef struct{
    unsigned char letra;
    int peso;    
}no;

    //Arvore que conterá os nós
typedef struct  {
    no raiz;
    struct arvore *dir;
    struct arvore *esq;
    struct arvore *prox;
}arvore;

    //Lista que conterá as árvores
typedef struct{
    arvore *raiz;
    int tam;
}lista;

//funções
void inicializa_tab(unsigned int t[]);
void cria_lista(lista *L);
void cria_no(lista *L, unsigned int vet[]);
void insere_ordenado();