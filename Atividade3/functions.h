#define bool int
#define true 1
#define false 0
#define MAX 256

    //nó e seus dados
typedef struct No{
    char letra;
    int peso;
    struct No *dir;
    struct No *esq;
    struct No *prox;
}no;

    //Lista que conterá as árvores
typedef struct Lista{
    struct No *raiz;
    int tam;
}lista;

//funções -------
void inicializa_tab(unsigned int t[]);

//funções da lista
void cria_lista(lista *L);
void preenche_lista(lista *L, unsigned int vet[]);
void insere_ordenado(lista *L, no *N);
void imprimir_lista(lista *L);

//funções da arvore
no *remove_elem (lista *L);
no *montar_arvore(lista *L);
void imprimir_arvore(no *raiz, int tam);
char** memoria_dicionario(int colunas);