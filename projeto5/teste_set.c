#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define SET_USER_WEIGHT 440
#define GET_USER_WEIGHT 441

int main(int argc, char *argv[]) {
	if (argc != 3) {
        printf("Parametros foram passados de maneira errada\n ./teste_set uid weight\n");
		return -1;
	}
    if(syscall(SET_USER_WEIGHT, (int)argv[1], (int)argv[2]) == -1) {
		printf("Ocorreu um error de errno = %d\n", errno);
		return -1;
	}

	printf("O peso do usuario %d foi alterado para %d\n", (int)argv[1], (int)argv[1]);
	return 0;
}
