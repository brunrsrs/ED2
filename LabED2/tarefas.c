#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    long loc; //localizacao dele
    int chave;
    char tarefa[60];
    int dia, mes, ano;
}ToDo;

int cadastrar_todo(ToDo **t, int quant, int tam){
    if(quant < tam){
        srand(time(NULL)); //muda a seed de aleatoridade
        ToDo *novo = malloc(sizeof(ToDo));
        novo->chave = rand()%100; //gera uma chave aleatoria
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

void imprimir(ToDo **t, int quant) {
    int i, chave, flag = 0;
    
    printf("\n\tLista de tarefas:\n");
    for (i=0; i<quant; i++) 
        printf("%d - %s\n", t[i]->chave, t[i]->tarefa);

    printf("\nDigite a chave que deseja mostrar mais informacoes: ");
    scanf(" %d", &chave);

    for (i=0; i<quant; i++)
        if (chave == t[i]->chave) {
            flag = 1;
            break;
        }

    if (flag == 1) {
        FILE *arq;
        ToDo *novo = malloc(sizeof(ToDo));
        arq = fopen("ToDo.txt", "r");

        fseek(arq, t[i]->loc, 0);
        fscanf(arq, "%d ", &novo->chave);
        fscanf(arq, "%50[^\n]\n", novo->tarefa);
        fscanf(arq, "%d %d %d", &novo->dia, &novo->mes, &novo->ano);

        printf("\n\t------ Tarefa encontrada ------\n");
        printf("chave: %d\ntarefa: %s\ndata: %d/%d/%d\n", novo->chave, novo->tarefa, novo->dia, novo->mes, novo->ano);
        printf("\n\t-----------------------------\n");
        }
    
    else
        printf("\n\t------ Chave nao encontrada -------");
}

/*
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
*/

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
            fprintf(file, "%d\n", quant); //printa a quantidade nos 2 arquivos
            fprintf(index, "%d\n", quant);
            
        for(i = 0; i < quant; i++){
            aux = ftell(file); //marca a posição inicial da tarefa no arquivo
            //printando no arquivo de datas
            fprintf(file, "%d ", t[i]->chave);
            fputs(t[i]->tarefa, file);
            fputc('\n', file);
            fprintf(file, "%d %d %d\n", t[i]->dia, t[i]->mes, t[i]->ano);

            //printando no arquivo de indice
            fprintf(index, "%ld %d ", aux, t[i]->chave); //printa a localização e a chave
            fputs(t[i]->tarefa, index);
            fputc('\n', index);
        }
        printf("\n\tSalvo com sucesso!\n");
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
        fscanf(file, "%ld %d ", &novo->loc, &novo->chave);
        fscanf(file, "%50[^\n]", novo->tarefa);
        c[i] = novo;
        }
        printf("\nArquivo lido com sucesso!\n");
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