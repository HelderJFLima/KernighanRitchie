/* Exercise 1-21. Write a program "entab" that replaces strings of blanks by
   the minimum number of tabs and blanks to achieve the same spacing. Use the
   same tab stops as for "detab". When either a tab or a single blank would
   suffice to reach a tab stop, which should be given preference? */


#include <stdio.h>

#define MAXSIZE 1000    /* Maximum length of string of blanks */
#define TAB 8           /* Number of columns in a tab */
#define BLANK 0         /* Reading blank characters */
#define NORMAL 1        /* Reading other characters */

void tabstring(char string[], int tabsize, int position, int blanks, int maxsize);


/* entab: replace strings of blanks by the minimum number of tabs and blanks
   to achieve the same spacing. */

main()
{
    int c, nblk, pos, state;
    char tabstr[MAXSIZE];

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
                pos = 0;            /* 'pos' starts to be counted on each new line. */
        }
        else if(c != ' ' && state == BLANK)
        {
            state = NORMAL;

            tabstring(tabstr, TAB, pos, nblk, MAXSIZE); /* Make a string of tabs
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


/* tabstring: make an equivalent string of tabs and blanks from one made of just
              blanks. */

void tabstring(char str[], int tab, int pos, int blknum, int lim)
{
    int i, nblk, ntab, rpos;

    rpos = pos - (pos / tab) * tab;     /* Relative position of the last character
                                           (0, 1, 2, ..., tab - 1) */

    if(rpos != 0 && blknum < tab - rpos)        /* Out of tab stop; not enough */
    {                                           /* blanks to reach the next one */

        ntab = 0;                   /* Number of tabs to make the new string */

        nblk = blknum;              /* Number of blanks */

    }
    else if(rpos != 0 && blknum >= tab - rpos)  /* Out of tab stop; but the */
    {                                           /* blanks are enough */

        ntab = ( blknum - (tab - rpos) ) / tab + 1;

        nblk = blknum - (tab - rpos) - (ntab - 1) * tab;

    }
    else if(blknum < tab)                       /* On the tab stop; not enough */
    {                                           /* blanks to the next */

        ntab = 0;

        nblk = blknum;

    }
    else if(blknum >= tab)                      /* On the tab stop; blanks are */
    {                                           /* enough */

        ntab = blknum / tab;

        nblk = blknum - ntab * tab;

    }

                                    /* Make the string of tabs and blanks. */
    for(i = 0; i < ntab && i < lim - 1; ++i)
        str[i] = '\t';

    if(i < lim - 1)                     /* To prevent overflow */
    {
        for(i = ntab; i < ntab + nblk && i < lim - 1; ++i)
            str[i] = ' ';

        str[i] = '\0';
    }
    else
        str[i] = '\0';
}
