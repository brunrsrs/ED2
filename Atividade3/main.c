#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.c"

#define MAX 256

int main()  {

    int cmd; //usado no switch case
    int i; //usado em while e for

    int qtd_dicionario=0; //armazena quantos valores há no dicionario
    char arquivo[30]; //armazenará o nome do arquivo lido
    char *texto; //armazenará o arquivo de texto;
    char **dicionario; //onde será armazenado cada valor de char
    char *codificado_bin; //texto codificado em binario será armazenado
    char *codificado_ascii; //texto codificado em ascii será armazenado
    unsigned int tab[MAX]; //tabela de frequencia
    unsigned char conv[9]; //será usado para a função convert
    
    int colunas = 1; //(pois deverá ter tamanho + 1)
    int qtd_chars = 0; //tamanho do texto 
    int qtd_bin = 0; //conta quantos digitos binarios terão
    
    char aux; //auxiliar para leitura dos dados
    int aux_2; //auxiliar para leitura de inteiros
    int count=0; //auxiliar para contagens

    
    lista *L = malloc(sizeof(lista));
    no *N, *arvore;

    FILE *leitor;
    FILE *saida;

    do {
        selecao();
        scanf(" %d", &cmd);

        switch(cmd) {
            case 1:

            inicializa_tab(tab); //inicializa ela com zeros


            printf("Digite o nome do arquivo que deseja compactar (com a extensão .txt): "); //escolhe o arquivo que ira compactar
            scanf(" %[^\n]c", arquivo);

            leitor = fopen(arquivo, "r");
            if (!leitor) {  //testa se foi possivel abrir o arquivo
                printf("\n\tO arquivo não foi encontrado\n\n");
                break;
            }

            qtd_chars=0;
            while (!feof(leitor)) { //pega os valores pra tabela
                aux = fgetc(leitor);
                tab[aux]++;
                qtd_chars++;
            }
            qtd_chars++;

            texto = malloc((qtd_chars+1) * sizeof(char)); //aloca memoria pro texto

            count = 0;
            fseek(leitor, 0, SEEK_SET);
            while (!feof(leitor)) { //passa o texto para uma string
                aux = fgetc(leitor);
                texto[count] = aux;
                count++;
            }
            texto[qtd_chars+1] = '\0'; //coloca o operador para encerrar
            fclose(leitor);

            cria_lista(L);
            preenche_lista(L, tab);

            arvore = montar_arvore(L); //monta a arvore
            colunas += altura_arvore(arvore); //conta quantas colunas serão necessárias
            dicionario = memoria_dicionario(colunas); //aloca memoria para o dicionario
            gerar_dicionario(dicionario, arvore, "", colunas); //gera o dicionario baseado na arvore

            for (i=0; i<MAX; i++) //passa por todos os valores do dicionario
                if(strlen(dicionario[i]) > 0) //caso nao esteja vazio o vetor
                    qtd_dicionario++;
                
            //variavel qtd_chars nao precisará mais acumular valores do texto inicial
            qtd_chars = calcula_tamanho_string(dicionario, texto);

            if (qtd_chars%8 != 0)
                codificado_bin = malloc((qtd_chars + (8-(qtd_chars%8))) * sizeof(char));

            else
                codificado_bin = malloc(qtd_chars * sizeof(char));


            codificado_bin = codificar(dicionario, texto); //codifica o texto para binário
            qtd_bin = tam_string_bin(codificado_bin); //conta quantos elementos terão para operações futuras


            if (qtd_bin % 8 != 0){ //caso não seja multiplo de 8, concatena os 8 restantes 
                qtd_chars = (qtd_bin + (8-(qtd_bin%8)))/8; //qtd de chars que terão pós operação
                for (i=0; i<8-(qtd_bin%8); i++) {
                    strcat(codificado_bin, "0");
                }
            }
            else
                qtd_chars = qtd_bin/8;

            //armazena memoria pro string que há de vir
            codificado_ascii = malloc(qtd_chars+1 * sizeof(char));
            if (!codificado_ascii) {
                printf("\n\tNão foi possivel alocar memoria\n");
                break;
            }

            for (i=0; i<qtd_chars; i++)
                codificado_ascii[i] = convert_byte(codificado_bin+(8*i), 8); //posição do codificado_bin
            codificado_ascii[qtd_chars+1] = '\0';

            /* muda a extensão do arquivo de saida que, como
            é convenientemente do mesmo tamanho da
            extensão inicial, nao precisa alocar memória extra */
            arquivo[strlen(arquivo)-3] = 'h';
            arquivo[strlen(arquivo)-2] = 'u';
            arquivo[strlen(arquivo)-1] = 'f';
            saida = fopen(arquivo,"w");

            //printa quantos n° binarios e quantos chars do dicionario serão usados
            fprintf(saida, "%d %d\n", qtd_bin, qtd_dicionario);

            for (i=0; i<MAX; i++) //printa o dicionario na saida
                if(strlen(dicionario[i]) > 0) { //caso nao esteja vazio o vetor
                    fprintf(saida, "%c %d\n", i, tab[i]);
                }

            i=0;
            while(codificado_ascii[i] != '\0') {
                fputc(codificado_ascii[i], saida);
                i++;
            }

            printf("\n\tTexto compactado!\n");
            printf("Bits economizados: %d\n", calcula_bits(tab, dicionario));

            fclose(saida);
            break;

            case 2:

            printf("Digite o nome do arquivo que deseja descompactar (com extensão .huf): ");
            scanf(" %[^\n]c", arquivo);

            leitor = fopen(arquivo, "r");
            if (!leitor) {
                printf("\n\tArquivo não encontrado!\n\n");
                break;
            }

            inicializa_tab(tab);

            qtd_chars = 1;
            fscanf(leitor, "%d %d", &qtd_bin, &qtd_dicionario);
            fseek(leitor, 1, SEEK_CUR); //posiciona para ler o dicionario

            for(i=0; i<qtd_dicionario; i++) { //preenche a tabela
                aux = fgetc(leitor);
                fscanf(leitor, " %d\n", &tab[aux]);
                qtd_chars += tab[aux]; //conta quantos chars serão alocados de memoria
            }
            count = ftell(leitor); //posição pós dicionario

            aux_2 = 0;
            fseek(leitor, count, SEEK_SET);
            while (!feof(leitor) && aux!='\0') {
                aux = fgetc(leitor);
                aux_2++;
            }

            codificado_bin = malloc(((aux_2*8)+1) * sizeof(char)); //pois será preenchido por binarios

            fseek(leitor, count, SEEK_SET);
            for (i=0; i<aux_2; i++) {
                aux = getc(leitor);
                convert(aux, conv);
                strcat(codificado_bin, conv);
            }
            fclose(leitor);

            //monta a arvore baseada no arquivo lido:
            cria_lista(L);
            preenche_lista(L, tab);
            arvore = montar_arvore(L); //monta a arvore

            texto = malloc(qtd_chars+1 * sizeof(char));
            codificado_bin[qtd_bin+1] = '\0'; //realoca o tamanho ignorando os numeros extras
            texto = decodificar(codificado_bin, arvore);

            arquivo[strlen(arquivo)-4] = '_';
            arquivo[strlen(arquivo)-3] = 'u';
            arquivo[strlen(arquivo)-2] = 'n';
            arquivo[strlen(arquivo)-1] = 'c';
            saida = fopen(strcat(strcpy(malloc(strlen(arquivo) + 12),arquivo),"ompressed.txt"),"w");
            
            for (i=0; i<qtd_chars-1; i++) //coloca o texto no arquivo
                fputc(texto[i], saida);

            printf("\n\tTexto descompactado!\n");

            fclose(saida);

            break;

            case 3:
            break;

            default:
            printf("\n\tOpção inválida\n");
        }
    } while (cmd!=3);

return 0;
}