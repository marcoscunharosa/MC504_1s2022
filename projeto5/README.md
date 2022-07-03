# Projeto 5 - Chamadas de Sistema no Kernel Linux


* Marcos Cunha Rosa - RA 240815
* Matheus Augusto da Silva Cândido - RA 241640
* Pedro Hori Bueno - RA 223402

## Sobre o projeto

O projeto 5 tem como objetivo o entendimento do papel das  chamadas de sistema no Kernel Linux entre o modo usuário e o modo kernel. Além disso, realizar a implementação de chamadas de sistema e de um teste para elas. Para realizar esse projeto seguimos o tutorial do [LKCamp](https://docs.lkcamp.dev/unicamp_group/systemcalls/) utilizando a função que está exemplificada no tutorial e em seguida realizamos os passos do tutorial mas agora com as chamadas criadas por nós.

## Video
[Explicação do Projeto](https://drive.google.com/file/d/1Jx-JWf7Y2QGEKjVyTuBAoPC8ZlUnKkiu/view)

## Sequencia de arquivos alterados no Kernel

```BASH
staging/arch/x86/entry/syscalls/syscall_64.tbl
staging/include/linux/syscalls.h
staging/include/uapi/asm-generic/unistd.h
staging/kernel/Makefile
staging/kernel/sys_ni.c
staging/kernel/memcpy.c
```
```BASH
staging/arch/x86/entry/syscalls/syscall_64.tbl
staging/include/linux/syscalls.h
staging/include/uapi/asm-generic/unistd.h
staging/kernel/Makefile
staging/kernel/sys_ni.c
staging/kernel/weighted_round_robin.c
```
O arquivo `memcpy.c` não está presente neste repositório pois é apresentado no tutorial do LKCamp. As chamadas implementadas pelo grupo estão no arquivo `weighted_round_robin.c`e os testes implementados estão nos arquivos `teste_get.c`e `teste_set.c`. Os demais arquivos editados fazem parte do Kernel Linux.
