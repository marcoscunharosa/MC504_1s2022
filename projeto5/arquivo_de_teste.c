#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <errno.h>

#define GET_USER_WEIGHT 429
#define SET_USER_WEIGHT 430

int main(int argc, char *argv[]) {
	if (argc != 3) {
        printf("Parametros foram passados de maneira errada");
		return -1;
	}
	
	criar_vetor();

	int weight = syscall(GET_USER_WEIGHT, atoi(argv[1]));

	if(weight == -1) {
		printf("Ocorreu um error de errno = %d\n", errno);
		return -1;
	}
	printf("O usuario %d possuia um peso igual à: %d\n", atoi(argv[1]), weight);

	if(syscall(SET_USER_WEIGHT, atoi(argv[1]), atoi(argv[2])) == -1) {
		printf("Ocorreu um error de errno = %d\n", errno);
		return -1;
	}
	weight = syscall(GET_USER_WEIGHT, atoi(argv[1]));
	if(weight == -1) {
		printf("Ocorreu um error de errno = %d\n", errno);
		return -1;
	}
	printf("O peso do usuario %d foi alterado para %d\n", atoi(argv[1]), weight);
	return 0;
}
