/* MC504 - Sistemas Operacionais 1s2022
    Projeto 1: Aplicação Multithread
    Alunos: Marcos Cunha Rosa - 240815
            Matheus Augusto da Silva Candido - 241640
            Pedro Hori Bueno - 223402
    Tema: Caça-palavras

    Esse projeto utiliza dos conceitos de multithreads para percorrer um caça-palavras.
    Utilizamos duas threads para cada palavra que deverá ser encontrada,
sendo que uma procura a palavra analisando as linhas, e outra analisando as colunas. 
    Para saber se a palavra foi encontrada por uma das threads, uma delas deverá ter como retorno o valor 1.

*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    char (* word)[9];
    char (* word_search)[9];

} thread_parameter;

/* Para este trabalho utilizamos uma struct com um campo para a palavra a ser procurada, e tambem o board do caça-palavras.
   Definimos um board de 9 linhas e 9 colunas, com um char por posição no board, contendo 5 palavras a serem encontradas.
   Assim, temos ao todo 10 threads no projeto.
*/

void * check_columns(void * params) { // procura uma palavra percorrendo as colunas da matriz
    thread_parameter * value = (thread_parameter *) params;
    char *word = value->word;
    int column = 0;
    int row = 0;
    int aux_word = 0;
    for (column=0; column < 9; column++){ // percorre cada coluna até encontrar ou não a palavra
        row = 0;
        while (row < 9){//percorre a coluna até encontra a palavra desejada ou até terminar a coluna
            if(word[aux_word] == value->word_search[row][column]){//verifica se a letra na posição analisada compõe a palavra na ordem necessaria
                aux_word++;
            }
            else{//caso encontre uma letra diferente da esperada na palavra, reinicia a posiçao a ser analisada na palavra
                aux_word = 0;
                if(word[aux_word] == value->word_search[row][column]){
                    aux_word++;
                }
            }

            if(aux_word == 9 || word[aux_word] == NULL){// se a palavra foi encontrada ele retornara da função com o valor 1
                return (void *) 1;
            }
            row++;
        }

    }
    return (void *) 0; // caso percorra todas as colunas e não encontre a palavra, retorna 0
}

void * check_rows(void * params) { // procura uma palavra percorrendo as linhas da matriz

    thread_parameter * value = (thread_parameter *) params;
    char *word = value->word;
    int column = 0;
    int row = 0;
    int aux_word = 0;
    for (row=0; row < 9; row++){
        column = 0;
        while (column < 9){// percorre a linha até encontrar a palavra ou terminar a linha
            //printf("%c / %c\n", word[aux_word], value->word_search[row][column]);
            if(word[aux_word] == value->word_search[row][column]){//verifica se a letra na posição analisada compõe a palavra na ordem necessaria
                aux_word++;
            }
            else{//caso encontre uma letra diferente da esperada na palavra, reinicia a posiçao a ser analisada na palavra
                aux_word = 0;
                if(word[aux_word] == value->word_search[row][column]){
                    aux_word++;
                }
            }

            if(aux_word == 9 || word[aux_word] == NULL){ // se a palavra foi encontrada ele retornara da função com o valor 1
                return (void *) 1;
            }
            column++;
        }

    }
    return (void *) 0; // caso percorra todas as linhas e não encontre a palavra, retorna 0
}
void main(){


char word_search[9][9] = {
            {'a', 'g', 'k', 'j', 'g', 'i', 'o', 'p', 'f'},
            {'j', 'v', 'c', 'k', 's', 'w', 'q', 'g', 'm'},
            {'h', 'u', 'n', 'i', 'c', 'a', 'm', 'p', 'c'},
            {'d', 'z', 'u', 'r', 't', 'n', 'b', 'l', 'l'},
            {'b', 'c', 'h', 'u', 'r', 'r', 'a', 's', 'o'},
            {'x', 'o', 'm', 'r', 'i', 'p', 's', 'e', 'v'},
            {'d', 'm', 'g', 'z', 'j', 'o', 'l', 'w', 'i'},
            {'a', 'p', 'b', 'x', 'k', 'd', 'o', 'c', 'n'},
            {'o', 'j', 'w', 's', 'e', 'r', 'g', 'e', 'l'}
        };
    // Thread to search word 1 = "unicamp"
    thread_parameter * parameter_word1 = (thread_parameter *) malloc(sizeof(thread_parameter));
    parameter_word1->word = "unicamp";
    parameter_word1->word_search = word_search;

    // Thread to search word 2 = "comp"
    thread_parameter * parameter_word2 = (thread_parameter *) malloc(sizeof(thread_parameter));
    parameter_word2->word = "comp";
    parameter_word2->word_search = word_search;

    // Thread to search word 3 = "sergel"
    thread_parameter * parameter_word3 = (thread_parameter *) malloc(sizeof(thread_parameter));
    parameter_word3->word = "sergel";
    parameter_word3->word_search = word_search;

    // Thread to search word 4 = "churras"
    thread_parameter * parameter_word4 = (thread_parameter *) malloc(sizeof(thread_parameter));
    parameter_word4->word = "churras";
    parameter_word4->word_search = word_search;

    // Thread to search word 5 = "mclovin"
    thread_parameter * parameter_word5 = (thread_parameter *) malloc(sizeof(thread_parameter));
    parameter_word5->word = "mclovin";
    parameter_word5->word_search = word_search;

    //Make threads
    pthread_t thread_1_row, thread_1_column,
    thread_2_row, thread_2_column,
    thread_3_row, thread_3_column,
    thread_4_row, thread_4_column,
    thread_5_row, thread_5_column;

    //Threads return values
    void * found_row_word1, *found_column_word1,
    *found_row_word2, *found_column_word2,
    *found_row_word3, *found_column_word3,
    *found_row_word4, *found_column_word4,
    *found_row_word5, *found_column_word5;

    // Starting threads.
    pthread_create(&thread_1_row, NULL, check_rows, (void *)parameter_word1);
    pthread_create(&thread_2_row, NULL, check_rows, (void *)parameter_word2);
    pthread_create(&thread_3_row, NULL, check_rows, (void *)parameter_word3);
    pthread_create(&thread_4_row, NULL, check_rows, (void *)parameter_word4);
    pthread_create(&thread_5_row, NULL, check_rows, (void *)parameter_word5);
    pthread_create(&thread_1_column, NULL, check_columns, (void *)parameter_word1);
    pthread_create(&thread_2_column, NULL, check_columns, (void *)parameter_word2);
    pthread_create(&thread_3_column, NULL, check_columns, (void *)parameter_word3);
    pthread_create(&thread_4_column, NULL, check_columns, (void *)parameter_word4);
    pthread_create(&thread_5_column, NULL, check_columns, (void *)parameter_word5);


    pthread_join(thread_1_row, &found_row_word1);
    pthread_join(thread_2_row, &found_row_word2);
    pthread_join(thread_3_row, &found_row_word3);
    pthread_join(thread_4_row, &found_row_word4);
    pthread_join(thread_5_row, &found_row_word5);
    pthread_join(thread_1_column, &found_column_word1);
    pthread_join(thread_2_column, &found_column_word2);
    pthread_join(thread_3_column, &found_column_word3);
    pthread_join(thread_4_column, &found_column_word4);
    pthread_join(thread_5_column, &found_column_word5);

    //printf("%d %d", (int)found_row_word3, (int)found_column_word3);

    if ( ((int) found_row_word1 == 1 || (int) found_column_word1 == 1) &&
    ((int) found_row_word2 == 1 || (int) found_column_word2 == 1) &&
    ((int) found_row_word3 == 1 || (int) found_column_word3 == 1) &&
    ((int) found_row_word4 == 1 || (int) found_column_word4 == 1) &&
    ((int) found_row_word5 == 1 || (int) found_column_word5 == 1) ){
        printf("Todas as palavras foram encontradas :-)\n");
    }
    else{
        printf("Ta faltando palavra :-(\n");
    }
}


