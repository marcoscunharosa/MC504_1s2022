# Projeto 2 - Aplicação de Multithreads com Semáforos


* Marcos Cunha Rosa - RA 240815
* Matheus Augusto da Silva Cândido - RA 241640
* Pedro Hori Bueno - RA 223402

## Sobre o projeto
O segundo projeto da disciplina de Sistema Operacionais visa explorar a aplicação de multithreads utilizando semáforos. Para isso, escolhemos como tema: "Produtor-Consumidor", onde em uma fábrica existe um produtor que adiciona produtos no estoque e enquanto isso consumidores entram na loja e só saem quando conseguem comprar um destes produtos. Foram criadas uma thread para o produtor, em que ele adiciona um produto no estoque e uma thread para cada consumidor, em que eles compram um produto do estoque. Foi utilizado três semáforos:
- estoque: o qual sinaliza quando há um produto disponível no estoque
- estoque_atualizado: estado em que uma ação na fábrica está sendo feita, seja o fabricante adicionando um produto ou um consumidor comprando um produto.
- sem_estados: estado em que é montado o print atual da fábrica. 


## Video
[Explicação do projeto](https://drive.google.com/file/d/16Et6eTj4hM5vUOHf0-1LA5UwWt5vZwH8/view?usp=drivesdk)

## Compilar e executar o código

~~~~
Compilação
gcc -o fabrica fabrica.c -lpthread
Execução:
./fabrica

