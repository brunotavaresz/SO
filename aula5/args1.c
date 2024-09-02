#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i;

    for(i = 0 ; i < argc ; i++) // argc é o número de argumentos
    {
        printf("Argument %02d: \"%s\"\n", i, argv[i]); // argv é um array de strings        
    }

    return EXIT_SUCCESS;
}
