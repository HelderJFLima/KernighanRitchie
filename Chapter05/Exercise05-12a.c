/* Exercise 5-12. Extend "entab" and "detab" to accept the shorthand
   "entab -m +n" to mean tab stops every "n" columns, starting at column "m".
   Choose convenient (for the user) default behavior. */


#include <ctype.h>      /* "isdigit" used by "copyarg" */
#include <stdio.h>
#include <stdlib.h>     /* "atoi" used by "readargs" */

#define MAXARG  100     /* Maximum size of an argument */
#define MAXSIZE 1000    /* Maximum length of string of blanks */
#define TAB 8           /* Default number of columns in a tab */
#define BLANK 0         /* Reading blank characters */
#define NORMAL 1        /* Reading other characters */
#define M 0             /* Argument alias */
#define N 1             /* Argument alias */

int copyarg(char num[], char arg[]);

int readargs(int argint[], char *argch[]);

void tabfill(char string[], int ntab, int nblk, int *i);

void tablank(int *tabnum, int *blknum, int position, int nblank, int tabsize);

void tabstring(char string[], int m, int n, int position, int blanks);


/* entab: replace strings of blanks by the minimum number of tabs and blanks
   to achieve the same spacing. */

main(int argc, char *argv[])
{
    int arg[2], c, nblk, pos, state;
    char tabstr[MAXSIZE];

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
                pos = 0;            /* 'pos' starts to be counted on each new */
                                    /* line. */
        }
        else if(c != ' ' && state == BLANK)
        {
            state = NORMAL;
                                        /* Make a string of tabs and blanks. */
            tabstring(tabstr, arg[M], arg[N], pos, nblk);

            printf("%s", tabstr);                               /** OUTPUT **/

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


/* tabfill: fill 'str' with the corresponding numbers of tabs and blanks. */

void tabfill(char str[], int ntab, int nblk, int *i)
{
    while(ntab-- > 0 && *i < MAXSIZE - 1)
        str[(*i)++] = '\t';

    if(*i < MAXSIZE - 1)                        /* To prevent overflow */
    {
        while(nblk-- > 0 && *i < MAXSIZE - 1)
            str[(*i)++] = ' ';
    }
}


/* tablank: calculate the number of tabs (*tabn) and blanks (*blkn) equivalent
            to a number of blanks (nblk). */

void tablank(int *tabn, int *blkn, int pos, int nblk, int tab)
{
    int rpos;

    rpos = pos % tab;               /* Relative position of the last character
                                       (0, 1, 2, ..., tab - 1) */

    if(rpos != 0 && nblk < tab - rpos)      /* Out of tab stop; not enough */
    {                                       /* blanks to reach the next one */

        *tabn = 0;                              /* Number of tabs */

        *blkn = nblk;                           /* Number of blanks */

    }
    else if(rpos != 0 && nblk >= tab - rpos)    /* Out of tab stop; but */
    {                                           /* the blanks are enough */

        *tabn = ( nblk - (tab - rpos) ) / tab + 1;

        *blkn = ( nblk - (tab - rpos) ) % tab;

    }
    else if(nblk < tab)                         /* On the tab stop; not enough */
    {                                           /* blanks to the next */

        *tabn = 0;

        *blkn = nblk;

    }
    else if(nblk >= tab)                        /* On the tab stop; blanks are */
    {                                           /* enough */

        *tabn = nblk / tab;

        *blkn = nblk % tab;

    }
}


/* tabstring: make an equivalent string of tabs and blanks from one made of just
              blanks. */

void tabstring(char str[], int m, int n, int pos, int blkn)
{
    int i, nblk, ntab;

    i = 0;

    if(pos < m && pos + blkn <= m)
    {

        tablank(&ntab, &nblk, pos, blkn, TAB);  /* Calculate the numbers of */
                                                /* tabs and blanks. */

        tabfill(str, ntab, nblk, &i);           /* Fill with tabs and blanks. */

    }
    else if(pos < m)
    {
        tablank(&ntab, &nblk, pos, m - pos - 1, TAB);

        tabfill(str, ntab, nblk, &i);

        tablank(&ntab, &nblk, m - 1, blkn - m + pos + 1, n);

        tabfill(str, ntab, nblk, &i);
    }
    else
    {
        tablank(&ntab, &nblk, pos, blkn, n);

        tabfill(str, ntab, nblk, &i);
    }

    str[i] = '\0';
}
