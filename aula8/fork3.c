#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("Pai (antes do fork): PID = %u, PPID = %u\n", getpid(), getppid()); // código do pai e do filho
    switch (fork()) // duplica o processo 
    {
      case -1: /* fork falhou */ // erro
               perror("Erro no fork\n"); // imprime mensagem de erro
               return EXIT_FAILURE; // termina com um código de erro
      case 0:  /* processo filho */ // código do filho
               if (execl("./child", "./child", NULL) < 0) {  // erro
                   perror("erro no lancamento da aplicacao"); // imprime mensagem de erro
                   return EXIT_FAILURE; // termina com um código de erro
               }
               printf("Porque é que eu não apareço?\n"); 
               break;
      default: /* processo pai */ // código do pai
               sleep(1); // espera 1 segundo
               printf("Pai (depois do fork): PID = %u, PPID = %u\n", getpid(), getppid()); // código do pai e do filho
    }

    return EXIT_SUCCESS;
}
