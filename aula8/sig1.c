#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    unsigned int i; // variável para guardar o contador

    printf("PID = %u\n", getpid()); // imprime o PID do processo atual
    i = 0; // inicializa o contador
    while (i <= 10) { // ciclo de 10 iterações
        printf("\r%08u ", i++); // imprime o valor de i com 8 dígitos e um espaço no início da linha
        fflush(stdout); // força a impressão do buffer de saída
        sleep(1); // espera 1 segundo
    }
    printf("\n"); // imprime uma nova linha

    return EXIT_SUCCESS;
}
