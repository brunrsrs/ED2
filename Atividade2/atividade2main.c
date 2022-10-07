#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atividade2.c"

int main()  {
int op=0, tamanho=0, desloc, aux, aux2, num;
FILE *arqDados, *arqIndice;
struct aluno A;

do {
    Menu();
    printf("Comando: ");
    scanf(" %d", &op);

    switch(op) {
        //Inserção
        case 1: 
        if (!Recebe(&A)) {
            printf("Não foi possível inserir");
            break;
        }
        //Operações no turma.txt
        //Tenta abrir o arquivo pra leitura e escrita se nao retorna NULL
        arqDados = fopen("turma.txt", "r+");
        if (!arqDados)
            arqDados = fopen("turma.txt", "w+");

        fseek(arqDados, 0, SEEK_END); //Move o ponteiro para o fim do arquivo
        fprintf(arqDados, "%02ld%s|%02ld%s|%d|", strlen(A.nome), A.nome, strlen(A.curso), A.curso, A.nro_UNESP);
            //o 2 são os numeros de chars de cada txt, o 9 é o N° do RA que tem 9 digitos e 3 são as "|"
        tamanho = 2 + strlen(A.nome) + 2 + strlen(A.curso) + 9 + 3; 
        for (int n=0;n<128-tamanho; n++)
            fprintf(arqDados, "#");

        fclose(arqDados);

        //Operações no index.txt
        //Tenta abrir o arquivo pra leitura e escrita se nao retorna NULL
        arqIndice = fopen("index.txt", "r+");
        if (!arqIndice)
            arqIndice = fopen("index.txt", "w+");

        desloc = -1;
        while (!feof(arqIndice)){ //auxiliares apenas usados pro deslocamento
            fscanf(arqIndice, "%d %d", &aux, &aux2);
            desloc++;
        }
        fprintf(arqIndice, "%d %d\n", A.nro_UNESP, desloc*128);
        fclose(arqIndice);
        break;
        
        //Busca
        case 2:

        if (!buscaRA(&desloc)) {
            printf("Não foi possivel encontrar\n");
            break;
        }
        
        arqDados = fopen("turma.txt", "r+");
        if (!arqDados)
            arqDados = fopen("turma.txt", "w+");
        
        fseek(arqDados, desloc, SEEK_SET);
        fscanf(arqDados, "%d", &aux);
        A.nome = malloc((aux+1) * sizeof(char));
        fgets(A.nome, aux+1, arqDados);
        
        fseek(arqDados, 1, SEEK_CUR); //se move pro proximo endereço
        fscanf(arqDados, "%d", &aux);
        A.curso = malloc((aux+1) * sizeof(char));
        fgets(A.curso, aux+1, arqDados);

        fseek(arqDados, 1, SEEK_CUR); //se move pro proximo endereço
        fscanf(arqDados, "%d", &A.nro_UNESP);

        printf("\nAluno: %s\nCurso: %s\nRA: %d\n\n", A.nome, A.curso, A.nro_UNESP); //Mostra na tela o resultado
        break;

        //Encerra o programa
        case 3: 
            printf("\n\tObrigado por utiliar ;)\n");
        break;

        //Valores inválidos
        default: printf("\n\tValor inválido!\n");
    }
} while(op!=3);

return 0;
}