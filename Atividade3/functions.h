#define bool int
#define true 1
#define false 0
#define MAX 256

typedef struct Dados{
    unsigned char letra;
    int peso;
}dados;

    //nó e seus dados
typedef struct No{
    struct Dados valor;
    struct No *dir;
    struct No *esq;
    struct No *prox;
}no;

    //Lista que conterá as árvores
typedef struct Lista{
    struct No *raiz;
    int tam;
}lista;

//funções
void inicializa_tab(unsigned int t[]);
void cria_lista(lista *L);
void cria_no(lista *L, unsigned int vet[]);
void insere_ordenado(lista *L, no *N);