#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <errno.h>

#define __NR_setuserweight 430

int main(int argc, char *argv[]) {
	if (argc != 3) {
        printf("Parametros foram passados de maneira errada\n ./teste_set uid weight\n");
		return -1;
	}
	int uid = atoi(argv[1]);
	int weight = atoi(argv[2]);

    if(syscall(__NR_setuserweight, uid, weight) == -1) {
		printf("Ocorreu um error de errno = %d\n", errno);
		return -1;
	}

	printf("O peso do usuario %d foi alterado para %d\n", uid, weight);
	return 0;
}
