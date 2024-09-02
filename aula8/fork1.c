#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int ret; // variável para guardar o valor de retorno do fork

    printf("Antes do fork: PID = %d, PPID = %d\n", getpid(), getppid()); // código do pai e do filho 
    if ((ret = fork()) < 0) { // erro 
        perror ("erro na duplicação do processo"); // imprime mensagem de erro
        return EXIT_FAILURE; // termina com um código de erro
    }
    if (ret > 0) sleep (1); 
    printf("Quem sou eu?\nApós o fork: PID = %d, PPID = %d\n", getpid(), getppid()); // código do pai e do filho  

    return EXIT_SUCCESS; // termina com um código de sucesso
}
