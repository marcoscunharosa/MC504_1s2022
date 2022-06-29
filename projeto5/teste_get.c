#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define SET_USER_WEIGHT 440
#define GET_USER_WEIGHT 441

int main(int argc, char *argv[]) {
	if (argc != 2) {
        printf("Parametros foram passados de maneira errada.\n ./teste_get uid\n");
		return -1;
	}

    int weight = syscall(GET_USER_WEIGHT, (int)argv[1]);

	if(weight == -1) {
		printf("Ocorreu um error de errno = %d\n", errno);
		return -1;
	}
    printf("O usuario %d possui um peso igual à: %d\n", (int)argv[1], weight);
    return(0)
}