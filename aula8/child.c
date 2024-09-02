#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    printf("Filho: PID = %d, PPID = %d\n", getpid(), getppid()); // código do filho 
    sleep(3); // espera 3 segundos
    printf("Filho: PID = %d, PPID = %d\n", getpid(), getppid()); // código do filho 

    return EXIT_SUCCESS; // termina com um código de sucesso
}
