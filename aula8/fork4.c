#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int stat;

    printf("Pai (antes do fork): PID = %u, PPID = %u\n", getpid(), getppid()); // código do pai e do filho
    switch (fork())
    {
      case -1: /* fork falhou */ // erro
               perror("Erro no fork\n"); // imprime mensagem de erro
               return EXIT_FAILURE;
      case 0:  /* processo filho */ // código do filho
               if (execl("./child", "./child", NULL) < 0) {  // erro
                   perror("erro no lancamento da aplicacao"); // imprime mensagem de erro
                   return EXIT_FAILURE;
               }
               break;
      default: /* processo pai */ // código do pai
               printf("Pai (depois do fork): PID = %u, PPID = %u\n", getpid(), getppid()); // código do pai e do filho
               if (wait(&stat) < 0) {  // erro 
                   perror("erro na espera da terminação do processo-filho"); // imprime mensagem de erro
                   return EXIT_FAILURE;
               }
               printf("Pai: o processo-filho terminou. "); 
               if (WIFEXITED(stat) != 0) { // processo terminou normalmente
                   printf("O seu status de saída foi %d.\n", WEXITSTATUS(stat)); // imprime o status de saída
               }
               else {
                   printf("O processo filho terminou de forma anormal.\n"); // imprime mensagem de erro
               }
    }

    return EXIT_SUCCESS;
}
