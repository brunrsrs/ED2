#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int chave;
    char tarefa[60];
    int dia, mes, ano;
}ToDo;

int cadastrar_todo(ToDo **t, int quant, int tam){
    if(quant < tam){
        ToDo *novo = malloc(sizeof(ToDo));
        printf("\nDigite a Tarefa: ");
        scanf("%50[^\n]", novo->tarefa);
        printf("\nDigite a data prevista dd mm aaaa: ");
        scanf("%d%d%d", &novo->dia, &novo->mes, &novo->ano);
        getchar();
        t[quant] = novo;
        return 1;
    }
    else{
        printf("\n\tERRO! Vetor cheio!\n");
        return 0;
    }
}

void imprimir(ToDo **t, int quant){
    int i;
    printf("\n\t------ Lista de Tarefas ------\n");
    for(i = 0; i < quant; i++){
        printf("\t%d = %2d/%2d/%4d\t%s\n", i+1,
        t[i]->dia, t[i]->mes, t[i]->ano, t[i]->tarefa);
    }
    printf("\t--------------------------------\n");
}

void alterar_todo(ToDo **t, int quant){
    int id;
    imprimir(t, quant);
    printf("\n\tDigite a tarefa a ser alterada: \n");
    scanf("%d", &id);
    getchar();
    id--;
    if(id >= 0 && id < quant){
        ToDo *novo = malloc(sizeof(ToDo));
        printf("\nDigite a nova tarefa: ");
        scanf("%50[^\n]", novo->tarefa);
        printf("\nDigite a data da tarefa dd mm aaaa: ");
    }
    else
        printf("\n\tCodigo invalido!\n");
}

void salvar(ToDo **t, int quant, char arq[]){
    FILE *file = fopen(arq, "w");
    FILE *index = fopen("index.txt", "w");
    int i;
    long aux;
    if(!file)
        printf("\n\tERRO AO ABRIR/CRIAR O ARQUIVO DE DATAS!\n");
    else if (!index)
        printf("\n\tERRO AO ABRIR/CRIAR O ARQUIVO DE INDICE!\n");
    else {
            fprintf(file, "%d\n", quant);
            fprintf(index, "%d\n", quant);
        for(i = 0; i < quant; i++){
            aux = ftell(file);
            //printando no arquivo de datas
            fprintf(file, "%d ", t[i]->chave);
            fputs(t[i]->tarefa, file);
            fputc('\n', file);
            fprintf(file, "%d %d %d\n", t[i]->dia, t[i]->mes, t[i]->ano);

            //printando no arquivo de indice
            fprintf(index, "%ld %d ", aux, t[i]->chave); //printa a localização 
            fputs(t[i]->tarefa, file);
            fputc('\n', index);
        }
        fclose(index);
        fclose(file);
    }
}

int ler_arquivo(ToDo **c){
    FILE *file = fopen("index.txt", "r");
    int i, quant=0;
    long aux;
    ToDo *novo;
    if(file){
        fscanf(file, "%d\n", &quant);
    for(i = 0; i < quant; i++){
        novo = malloc(sizeof(ToDo));
        fscanf(file, "%ld %d ", &aux, &novo->chave);
        fscanf(file, "%50[^\n]", novo->tarefa);
        c[i] = novo;
        }
    }
    else
        printf("\n\tERROR AO ABRIR/CRIAR O ARQUIVO!\n");

    fclose(file);
    return quant;
}

int main(){
    ToDo *tarefa[100];
    char arquivo[] = {"ToDo.txt"};
    int opcao, tam = 100, quant = 0;
    do{
        printf("\n\t0 - Sair\n\t1 - Cadastrar\n\t2 - Alterar\n\t3 - Imprimir\n\t4 - Salvar\n\t5 - Ler arquivo\n");
        scanf("%d", &opcao);
        getchar();
        switch(opcao){
            case 1:
                quant += cadastrar_todo(tarefa, quant, tam);
                break;
            case 2:
//                alterar_todo(tarefa, quant);
                printf("\nEssa funcao provavelmente vai quebrar\n");
                break;
            case 3:
                imprimir(tarefa, quant);
                break;
            case 4:
                salvar(tarefa, quant, arquivo);
                break;
            case 5:
                quant = ler_arquivo(tarefa);
                break;
            default:
                if(opcao != 0)
                printf("\n\tOpcao invalida!!!\n");
        }
    }while(opcao != 0);
    return 0;
}