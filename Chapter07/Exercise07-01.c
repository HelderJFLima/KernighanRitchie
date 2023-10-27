/* Exercise 7-1. Write a program that converts upper case to lower or lower case
   to upper, depending on the name it is invoked with, as found in "argv[0]". */


#include <ctype.h>      /* For tolower, toupper */
#include <stdio.h>
#include <string.h>     /* For strcmp */

#define TOLOWER 1       /* Conversion modes */
#define TOUPPER 2


int readarg(char *args[]);


/* Convert input to lower or to upper case depending on the argument it is
   invoked with. */

main(int argc, char *argv[])
{
    int arg, c;
    int (*convfunc)(int);                   /* Pointer to conversion function */

    if( ( arg = readarg(argv) ) == 0 )      /* Read the argument and */
                                            /* test if it is valid. */
        return 1;

    else if(arg == TOLOWER)                 /* Choose conversion function. */

        convfunc = tolower;

    else
        convfunc = toupper;

    while( ( c = getchar() ) != EOF )       /* Input / output */
        putchar( (*convfunc)(c) );

    return 0;
}


/* readarg: read an argument and return its type; return 0 if there are any
            errors. */

int readarg(char *args[])
{
    if(args[1] == NULL)
    {
        printf("\n* ERROR *: no argument given\n\n");

        return 0;
    }
    else if(strcmp(args[1], "tolower") == 0)

        return TOLOWER;

    else if(strcmp(args[1], "toupper") == 0)

        return TOUPPER;

    else
    {
        printf("\n* ERROR *: unknown argument: %s\n\n", args[1]);

        return 0;
    }
}
