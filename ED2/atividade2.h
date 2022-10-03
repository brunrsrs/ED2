#define TRUE 1
#define FALSE 0
#define bool int

//Definindo o registro
struct aluno {
    char *nome;
    char *curso;
    int nro_UNESP;
};

//Funções
void Menu();
bool Recebe(struct aluno *A);
bool BuscaRA(int *desloc);
