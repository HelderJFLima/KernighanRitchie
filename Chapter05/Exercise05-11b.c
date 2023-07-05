/* Exercise 5-11. Modify the program "entab" and "detab" (written as exercises
   in Chapter 1) to accept a list of tab stops as arguments. Use the default
   tab settings if there are no arguments. */


#include <stdio.h>

#define MAXARG  100     /* Maximum size of an argument */
#define MAXLIST  100    /* Maximum size of argument list */
#define TAB 8           /* Default number of columns in a tab */

int tablist(int array[], char *args[]);


/* detab: replace tabs in the input with the proper number of blanks */

main(int argc, char *argv[])
{
    int c, n, nstp, pos, tabstp[MAXLIST];

    if( !tablist(tabstp, argv) )    /* If there is any argument problem */
        return 1;

    pos = 0;                        /* Position in the line */

    printf("\nEnter a text:\n\n");

    while( (c = getchar()) != EOF )
    {
        if(c != '\t')
        {
            putchar(c);

            ++pos;

            if(c == '\n')           /* 'pos' starts to be counted */
                pos = 0;            /* on each new line. */
        }
        else                        /* Replace a tab. */
        {
            if( pos < tabstp[argc - 1] )        /* Tabulation from arguments */
            {
                                        /* Find the next tab stop if exists. */
                for(nstp = 0; tabstp[nstp] <= pos; nstp++)
                    ;

                n = tabstp[nstp] - pos; /* Number of spaces to put in the line */

                while(n-- > 0)
                {
                    putchar(' ');

                    ++pos;
                }
            }
            else                                /* Default tabulation */
            {
                n = TAB - (pos % TAB);

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


/* tablist: convert a list of arguments to an array of integers; return 0 if
            there is some invalid argument and 1 otherwise. */

int tablist(int arr[], char *args[])
{
    int i, j;
    char arg[MAXARG];

    i = j = 0;

    *arr++ = 0;

    while(*++args != NULL)
    {
        while( (*args)[i] != '\0' )                 /* Read each argument. */
        {
            if( isdigit( (*args)[i] ) )

                arg[j++] = (*args)[i++];

            else
            {
                printf("\n* ERROR *: invalid argument: %s\n\n", *args);

                return 0;
            }
        }

        arg[j] = '\0';

        *arr = atoi(arg);                           /* Convert to integer. */

        if( *arr <= *(arr - 1) )
        {
            printf("\n* ERROR *: invalid tab stop order: ");

            printf("%d %d\n\n", *(arr - 1), *arr);

            return 0;
        }
        else
            arr++;

        i = j = 0;
    }

    return 1;
}
