#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.c"

#define MAX 256

int main()  {

    int cmd;

    do {
        selecao();
        scanf(" %d", &cmd);

        switch(cmd) {
            case 1:;

            int i; //usado em while e for
            int colunas = 1; //(pois deverá ter tamanho + 1)
            int qtd_chars = 0; //tamanho do texto 
            int qtd_bin = 0; //conta quantos digitos binarios terão
            int qtd_dicionario=0; //armazena quantos valores há no dicionario

            char arquivo[30];
            char *texto; //armazenará o arquivo de texto;
            char **dicionario; //onde será armazenado cada valor de char
            char *codificado_bin; //texto codificado em binario será armazenado
            char *codificado_ascii; //texto codificado em ascii será armazenado

            unsigned int tab[MAX]; //tabela de frequencia
            inicializa_tab(tab); //inicializa ela com zeros

            lista *L = malloc(sizeof(lista));
            no *N, *arvore;

            FILE *leitor;
            FILE *compac;

            printf("Digite o nome do arquivo que deseja compactar (com a extensão .txt): "); //escolhe o arquivo que ira compactar
            scanf(" %[^\n]c", arquivo);

            leitor = fopen(arquivo, "r");
            if (!leitor) {  //testa se foi possivel abrir o arquivo
                printf("\n\tO arquivo não foi encontrado\n\n");
                break;
            }

            //printf("O programa irá gerar um arquivo com texto codificado_bin:\n");

            char aux;
            while (!feof(leitor)) { //pega os valores pra tabela
                aux = fgetc(leitor);
                tab[aux]++;
                qtd_chars++;
            }

            texto = malloc((qtd_chars+1)*sizeof(char)); //aloca memoria pro texto

            int count=0;
            fseek(leitor, 0, SEEK_SET);
            while (!feof(leitor)) { //passa o texto para uma string
                aux = fgetc(leitor);
                texto[count] = aux;
                count++;
            }
            texto[qtd_chars+1] = '\0'; //coloca o operador para encerrar
            fclose(leitor);

            printf("\n\tTexto lido:\n");
            mostra_texto(texto, qtd_chars);

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

            codificado_bin = malloc(qtd_chars * sizeof(char));
            codificado_bin = codificar(dicionario, texto); //codifica o texto para binário
            qtd_bin = tam_string_bin(codificado_bin); //conta quantos elementos terão para operações futuras

            printf("\n\tTexto pós binário:\n");
            mostra_texto(codificado_bin, qtd_bin);

            if (qtd_bin % 8 != 0) //caso não seja multiplo de 8, concatena os 8 restantes
                qtd_chars = (qtd_bin + (8-(qtd_bin%8)))/8; //qtd de chars que terão pós operação
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

            FILE *saida;
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
                    fprintf(saida, "%c %s\n", i, dicionario[i]);
                }
            
            printf("\n\tTexto codificado:\n");
            mostra_texto(codificado_ascii, qtd_chars);

            i=0;
            while(codificado_ascii[i] != '\0') {
                fputc(codificado_ascii[i], saida);
                i++;
            }
            fclose(saida);
            break;

            case 2:;

            char arquivo[30];

            printf("Digite o nome do arquivo que deseja descompactar (com a extensão .huf): "); //escolhe o arquivo que ira descompactar
            scanf(" %[^\n]c", arquivo);


            break;

            case 3:
            break;

            default:
            printf("\n\tOpção inválida\n");
        }
    } while (cmd!=3);

    printf("\nObrigado por utilizar ;)\n\n");
return 0;
}