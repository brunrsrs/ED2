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

//funções gerais-------
void selecao();
void mostra_texto(char *t, int size);
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
int altura_arvore(no *raiz);

//funções do dicionario
char** memoria_dicionario(int colunas);
void gerar_dicionario(char **dicionario, no *raiz, char *caminho, int colunas);
void imprime_dicionario(char **dicionario);

//funções pra codificação
int calcula_tamanho_string(char **dicionario, unsigned char *tex);
char* codificar(char **dicionario, unsigned char *texto);
char* decodificar(unsigned char texto[], no *raiz);
int tam_string_bin(char *texto);

//funções de conversão
char convert_byte (char *vet , int n);
void convert (char ch, char *Vet);

//funções de calcular o tamanho
int calcula_bits(unsigned int tab[], char** dicionario);