#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <errno.h>

#define __NR_getuserweight 429

int main(int argc, char *argv[]) {
	if (argc != 2) {
        printf("Parametros foram passados de maneira errada.\n ./teste_get uid\n");
		return -1;
	}

    int weight = syscall(__NR_getuserweight, (int)argv[1]);

	if(weight == -1) {
		printf("Ocorreu um error de errno = %d\n", errno);
		return -1;
	}
    printf("O usuario %d possui um peso igual à: %d\n", (int)argv[1], weight);
    return(0);
}
