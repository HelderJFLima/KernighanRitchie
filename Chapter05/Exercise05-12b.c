/* Exercise 5-12. Extend "entab" and "detab" to accept the shorthand
   "entab -m +n" to mean tab stops every "n" columns, starting at column "m".
   Choose convenient (for the user) default behavior. */


#include <ctype.h>      /* "isdigit" used by "copyarg" */
#include <stdio.h>
#include <stdlib.h>     /* "atoi" used by "readargs" */

#define MAXARG  100     /* Maximum size of an argument */
#define TAB 8           /* Default number of columns in a tab */
#define M 0             /* Argument alias */
#define N 1             /* Argument alias */

int copyarg(char num[], char arg[]);

int readargs(int argint[], char *argch[]);


/* detab: replace tabs in the input with the proper number of blanks */

main(int argc, char *argv[])
{
    int arg[2], c, n, pos;

    if(argc == 3)                   /* Arguments tabulation */
    {
        if( !readargs(arg, argv) )
            return 1;
    }
    else if(argc == 1)              /* Default tabulation */
    {
        arg[M] = 0;

        arg[N] = TAB;
    }
    else
    {
        printf("\n* ERROR *: invalid number of arguments\n\n");

        return 2;
    }

    pos = 0;                        /* Position in the line */

    printf("\nEnter a text:\n\n");

    while( (c = getchar()) != EOF )
    {
        if(c != '\t')
        {
            putchar(c);

            ++pos;

            if(c == '\n')           /* 'pos' starts to be counted on each new */
                pos = 0;            /* line. */
        }
        else                        /* Replace a tab. */
        {
            if(pos >= arg[M])           /* Tabulation from arguments */
            {
                n = arg[N] - (pos - arg[M]) % arg[N] - 1;

                if(n == 0)
                    n = arg[N];

                while(n-- > 0)
                {
                    putchar(' ');

                    ++pos;
                }
            }
            else                        /* Default tabulation */
            {
                if(arg[M] - pos > TAB + 1)

                    n = TAB - (pos % TAB);

                else
                    n = arg[M] - pos - 1;

                while(n-- > 0)
                {
                    putchar(' ');

                    ++pos;
                }
            }
        }
    }

    return 0;
}


/* copyarg: copy an argument to an array; return 0 if there is any problem with
            the argument and 1 otherwise. */

int copyarg(char num[], char arg[])
{
    int i = 0;

    while(*arg != '\0')
    {
        if(isdigit(*arg) && i < MAXARG - 1)

            num[i++] = *arg++;

        else
            return 0;
    }

    num[i] = '\0';

    if(i > 0)

        return 1;

    else
        return 0;
}


/* readargs: read two arguments and convert them to integers; return 0 if there
             is some error and 1 otherwise.*/

int readargs(int argint[], char *argch[])
{
    char num[MAXARG];

    while(*++argch != NULL)
    {
        if(**argch == '-')                  /* First argument '-m' */
        {
            if( copyarg(num, *argch + 1) )  /* Copy and convert to integer. */

                argint[M] = atoi(num);

            else
            {
                printf("\n* ERROR *: invalid argument: %s\n\n", *argch);

                return 0;
            }
        }
        else if(**argch == '+')             /* Second argument '+n' */
        {
            if( copyarg(num, *argch + 1) )

                argint[N] = atoi(num);

            else
            {
                printf("\n* ERROR *: invalid argument: %s\n\n", *argch);

                return 0;
            }
        }
        else
        {
            printf("\n* ERROR *: unknown argument: %s\n\n", *argch);

            return 0;
        }
    }

    return 1;
}
