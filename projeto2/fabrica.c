#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define N_compradores 10

sem_t estoque;
sem_t estoque_atualizado;
sem_t sem_estados;


typedef enum {C, S} estado_estoque;
typedef enum {CL, SL} estado_loja;
estado_estoque estado_estoque_loja[N_compradores];
estado_loja estado_da_loja[N_compradores];
int clientesLOJA[N_compradores];
int clienteExit =-1;

void imprimeCineminha() {
  int i, j, titulo = 0;
  

  titulo = (2 + 5 * N_compradores)/2;
  titulo -= 1;

  for (i = 0; i < titulo; i++) {
    printf(" ");
  }
  printf("LOJA\n");

  /***********************************************************************
   *************************** PRIMEIRA LINHA ***************************/

  printf ("/ ");

  for (i = 0; i < N_compradores; i++) {
    if (estado_estoque_loja[i] == C) {
      printf("  p  ");
    } else {
      printf("     ");
    }
  }
  printf("\\ \n");

  /*****************************************************************************
   ********************** FIM DA IMPRESSAO PRIMEIRA LINHA **********************
   ****************************************************************************/
  
  /*****************************************************************************
   ************************** IMPRESSAO SEGUNDA LINHA **************************
   ****************************************************************************/

  printf ("| ");

  for (i = 0; i < N_compradores; i++) {
    printf(" --- ");
  }

  printf ("| \n");

  /*****************************************************************************
   ********************** FIM DA IMPRESSAO SEGUNDA LINHA ***********************
   ****************************************************************************/
  
  /*****************************************************************************
   ************************* IMPRESSAO TERCEIRA LINHA **************************
   ****************************************************************************/

  printf("\\ ");
  for (i = 0; i < N_compradores; i++) {
    if (clientesLOJA[i] != -1) {
      printf(" %2d  ", clientesLOJA[i]);
    } else {
      printf("     ");
    }
  }
  printf("/ ");
  if (clienteExit == -1){
    printf("\n\n");
  }
  else{
    printf(" %2dp \n\n", clienteExit);
  }

}

void* f_fabrica(void *v) {
  int i;
    while(1) {
        sleep(1);
        sem_wait(&estoque_atualizado);
        sem_post(&estoque);

        sem_wait(&sem_estados);
        for (i = 0; i < N_compradores; i++) {
          if(estado_estoque_loja[i] == S){
            estado_estoque_loja[i] = C;
            break;
          }
        }
        imprimeCineminha();
        printf("A fabrica adicionou um produto ao estoque.\n");
        sem_post(&sem_estados);

        sem_post(&estoque_atualizado);
    }
    return(NULL);
}

void* f_comprador(void *v) {
    int i;
    int id = *(int*) v;
    sleep(random()%10);

    sem_wait(&sem_estados);
    for (i = 0; i < N_compradores; i++) {
      if(estado_da_loja[i] == SL){
        estado_da_loja[i] = CL;
        clientesLOJA[i] = id;
        break;
      }
    }
    imprimeCineminha();
    printf("O comprador %d deseja comprar um produto.\n", id);
    sem_post(&sem_estados);

    sem_wait(&estoque);
    sem_wait(&estoque_atualizado);

    sem_wait(&sem_estados);
    for (i = 0; i < N_compradores; i++) {
      if(estado_estoque_loja[i] == C){
        estado_estoque_loja[i] = S;
        break;
      }
    }
    clienteExit = id;

    for (i = 0; i < N_compradores-1; i++) {
      clientesLOJA[i] = clientesLOJA[i+1];
      if(estado_da_loja[i+1] == SL){
        estado_da_loja[i] = SL;
      }
      if(estado_da_loja[i+1] == CL){
        estado_da_loja[i] = CL;
      }
    }
    estado_da_loja[N_compradores] == SL;
    clientesLOJA[N_compradores] == -1;
    imprimeCineminha();
    printf("O comprador %d comprou um produto do estoque.\n", id);
    clienteExit = -1;

    sem_post(&sem_estados);

    sem_post(&estoque_atualizado);

}

int main() {
  pthread_t thr_comprador[N_compradores], thr_fabrica;
  int i, id[N_compradores];

  sem_init(&estoque, 0, 0);
  sem_init(&estoque_atualizado, 0, 1);

  sem_init(&sem_estados, 0, 1);

  for (i = 0; i < N_compradores; i++) {
    sem_wait(&sem_estados);
    estado_estoque_loja[i] = S;
    sem_post(&sem_estados);
  }
  for (i = 0; i < N_compradores; i++) {
    sem_wait(&sem_estados);
    estado_da_loja[i] = SL;
    sem_post(&sem_estados);
  }
  for (i = 0; i < N_compradores; i++) {
    sem_wait(&sem_estados);
    clientesLOJA[i] = -1;
    sem_post(&sem_estados);
  }
  imprimeCineminha();

  
  for (i = 0; i < N_compradores; i++) {
    id[i] = i;
    pthread_create(&thr_comprador[i], NULL, f_comprador, (void*) &id[i]);
  }

  pthread_create(&thr_fabrica, NULL, f_fabrica, NULL);
  
  for (i = 0; i < N_compradores; i++) 
    pthread_join(thr_comprador[i], NULL);  
  return 0;
}