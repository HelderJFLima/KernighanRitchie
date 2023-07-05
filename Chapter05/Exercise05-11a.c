/* Exercise 5-11. Modify the program "entab" and "detab" (written as exercises
   in Chapter 1) to accept a list of tab stops as arguments. Use the default
   tab settings if there are no arguments. */


#include <ctype.h>      /* "isdigit" used by "tablist" */
#include <stdio.h>
#include <stdlib.h>     /* "atoi" used by "tablist" */

#define MAXARG  100     /* Maximum size of an argument */
#define MAXLIST  100    /* Maximum size of argument list */
#define MAXSIZE 1000    /* Maximum length of string of blanks */
#define TAB 8           /* Default number of columns in a tab */
#define BLANK 0         /* Reading blank characters */
#define NORMAL 1        /* Reading other characters */

int tablist(int array[], char *args[]);

void tabstring(char string[], int argnum, int position, int blanks);


/* entab: replace strings of blanks by the minimum number of tabs and blanks
   to achieve the same spacing. */

main(int argc, char *argv[])
{
    int c, nblk, pos, state;
    static int tabstp[MAXLIST];
    char tabstr[MAXSIZE];

    if( !tablist(tabstp, argv) )    /* If there is any argument problem */
        return 1;

    nblk = 0;                       /* Number of blanks in the string of blanks */

    pos = 0;                        /* Position in the line */

    state = NORMAL;

    printf("\nEnter a text:\n\n");

    while( (c = getchar()) != EOF )
    {
        if(c != ' ' && state == NORMAL)
        {
            putchar(c);

            if(c != '\n')
                ++pos;
            else
                pos = 0;                    /* 'pos' starts to be counted */
        }                                   /* on each new line. */
        else if(c != ' ' && state == BLANK)
        {
            state = NORMAL;

            tabstring(tabstr, argc, pos, nblk);     /* Make a string of tabs
                                                       and blanks. */

            printf("%s", tabstr);                       /** OUTPUT **/

            putchar(c);

            if(c != '\n')
                pos = pos + nblk + 1;
            else
                pos = 0;

            nblk = 0;
        }
        else if(state == NORMAL)
        {
            state = BLANK;

            ++nblk;                 /* Count blanks. */
        }
        else
            ++nblk;
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


/* tabstring: make an equivalent string of tabs and blanks from one made of just
              blanks. */

void tabstring(char str[], int argn, int pos, int blkn)
{
    int deflt, i, nblk, nstp, ntab, rpos;
    static tabstp[MAXLIST];
    enum boolean {FALSE, TRUE};

                                        /* Find the next tab stop if exists. */
    for(nstp = 0; tabstp[nstp] <= pos && nstp < argn - 1; nstp++)
        ;

                                                /* Default tabulation or not */
    deflt = ( tabstp[nstp] <= pos ) ? TRUE : FALSE;

    i = 0;

    if(!deflt)                                  /* Tabulation from arguments */
    {
        while(blkn > 0 && i < MAXSIZE - 1)
        {
            if(blkn >= tabstp[nstp] - pos)      /* Fill with a tab. */
            {
                str[i++] = '\t';

                blkn -= (tabstp[nstp] - pos);

                pos += (tabstp[nstp] - pos);
            }
            else                                /* Fill with blanks. */
            {
                while(blkn-- > 0 && i < MAXSIZE - 1)
                    str[i++] = ' ';
            }

            if( pos >= tabstp[argn - 1] && i < MAXSIZE - 1)
            {
                deflt = TRUE;

                break;
            }
        }
    }

    if(deflt)                                   /* Default tabulation */
    {
        rpos = pos % TAB;           /* Relative position of the last character
                                       (0, 1, 2, ..., TAB - 1) */

        if(rpos != 0 && blkn < TAB - rpos)  /* Out of tab stop; not enough */
        {                                   /* blanks to reach the next one */

            ntab = 0;                       /* Number of tabs */

            nblk = blkn;                    /* Number of blanks */

        }
        else if(rpos != 0 && blkn >= TAB - rpos)    /* Out of tab stop; but */
        {                                           /* the blanks are enough */

            ntab = ( blkn - (TAB - rpos) ) / TAB + 1;

            nblk = ( blkn - (TAB - rpos) ) % TAB;

        }
        else if(blkn < TAB)                 /* On the tab stop; not enough */
        {                                   /* blanks to the next */

            ntab = 0;

            nblk = blkn;

        }
        else if(blkn >= TAB)                /* On the tab stop; blanks are */
        {                                   /* enough */

            ntab = blkn / TAB;

            nblk = blkn % TAB;

        }

        while(ntab-- > 0 && i < MAXSIZE - 1)
            str[i++] = '\t';

        if(i < MAXSIZE - 1)                     /* To prevent overflow */
        {
            while(nblk-- > 0 && i < MAXSIZE - 1)
                str[i++] = ' ';
        }
    }

    str[i] = '\0';
}
