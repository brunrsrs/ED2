#define bool int
#define true 1
#define false 0

    //Arvore que conterá os dados
typedef struct arvore {

char letra;
int peso;
struct arvore *dir;
struct arvore *esq;
} tree;

    //Lista que conterá as árvores
typedef struct lista {

tree arv;
struct lista *prox;
}list;