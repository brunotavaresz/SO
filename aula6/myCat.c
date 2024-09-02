#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* SUGESTÂO: utilize as páginas do manual para conhecer mais sobre as funções usadas:
 man fopen
 man fgets
*/

#define LINEMAXSIZE 80 /* or other suitable maximum line size */


int main(int argc, char *argv[])
{
    FILE *fp = NULL; // file pointer
    char line [LINEMAXSIZE]; // line buffer

    /* Validate number of arguments */
    if( argc != 2 ) // argc should be 2 for correct execution
    {
        printf("USAGE: %s fileName\n", argv[0]); // argv[0] is the program name
        return EXIT_FAILURE;
    }
    
    /* Open the file provided as argument */
    errno = 0;
    fp = fopen(argv[1], "r");
    if( fp == NULL )
    {
        perror ("Error opening file!");
        return EXIT_FAILURE;
    }

    /* Read all the lines of the file */
    int complete = 0;
    int count = 0;
    while( fgets(line, sizeof(line), fp) != NULL ) // read a line
    {
        if(complete == 1) // print line number
        {
            printf("%d ", count); 
        }
         printf("-> %s", line); 

        int linesize = strlen(line);
        if(linesize == LINEMAXSIZE - 1 && line[LINEMAXSIZE - 1] != '\n') // line is complete if it has the maximum size and the last character is not '\n'
        {
            complete = 0; // line is not complete
        }
        else
        {
            complete = 1;
            count++;
        }
    }

    fclose(fp);

    return EXIT_SUCCESS;
}
