/* Exercise 1-22. Write a program to "fold" long input lines into two or more
   shorter lines after the last non-blank character that occurs before the n-th
   column of input. Make sure your program does something intelligent with very
   long lines, and if there are no blanks or tabs before the specified column. */


#include <stdio.h>

#define MAXLINE 1000    /* Maximum input line length */
#define MAXSIZE 20      /* Maximum output line length */
#define TAB 8           /* Number of columns in a tab */
#define INLINE 1        /* Inside a short line */
#define OUTLINE 0       /* Outside a short line */
#define INWORD 1        /* Inside a word */
#define OUTWORD 0       /* Outside a word */

int getline_detab(char line[], int tabsize, int maxline);

void partialcopy(char to[], char from[], int start, int end);


/* Cut long input lines into shorter lines after the last non-blank character
   that occurs before the n-th column of input */

main()
{
    int fvchar, lvchar, pos;
    int lstate, wstate;
    char fulline[MAXLINE], shortline[MAXSIZE + 1];

    printf("\nEnter a text:\n\n");

    while( getline_detab(fulline, TAB, MAXLINE) > 0 )
    {
        lstate = OUTLINE;

        wstate = OUTWORD;

        fvchar = 0;                         /* First valid char position */

        lvchar = 0;                         /* Last valid char position */

        pos = 0;                            /* Position in the line */

        while(fulline[pos] != '\0')
        {
            while(pos - fvchar < MAXSIZE && fulline[pos] != '\0')
            {
                if(fulline[pos] != ' ' && wstate == INWORD)

                    ++pos;

                else if(fulline[pos] != ' ' && wstate == OUTWORD)
                {
                    wstate = INWORD;

                    if(lstate == OUTLINE)
                    {
                        lstate = INLINE;

                        fvchar = pos;       /* Start of the short line */
                    }

                    ++pos;
                }
                else if(wstate == INWORD)
                {
                    wstate = OUTWORD;

                    lvchar = pos - 1;       /* Possible end of the short line */

                    ++pos;
                }
                else
                {
                    if(lstate == OUTLINE)
                        fvchar = pos;

                    ++pos;
                }
            }

            if(lstate == INLINE)            /* If something valid was read */
            {
                if (fulline[pos] != '\0')
                {
                                            /* If it's still the first word of
                                               the short line */
                    if(lvchar <= fvchar && wstate == INWORD)
                        lvchar = pos - 1;

                }
                else if (wstate == INWORD)
                    lvchar = pos - 1;

                partialcopy(shortline, fulline, fvchar, lvchar);

                printf("%s\n", shortline);                      /** OUTPUT **/

                lstate = OUTLINE;

                wstate = OUTWORD;

                pos = fvchar = lvchar + 1;
            }
        }
    }

    return 0;
}


/* getline_detab: read a line into "s" and replace tabs with the proper number
                  of blanks; return length. */

int getline_detab(char s[], int tab, int lim)
{
    int c, i, j, n;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    {
        if(c != '\t')
            s[i] = c;
        else                                /* Replace a tab. */
        {
            n = tab - ( i - (i / tab) * tab );  /* Number of spaces to put in
                                                   the line */

            for(j = 0; j < n && i + j < lim - 1; ++j)
                s[i + j] = ' ';

            if(i + j < lim - 1 || j == n)       /* To prevent overflow */
                i = i + n - 1;
            else
                i = lim - 2;
        }
    }

    if(c == '\n')
    {
        s[i] = c;

        ++i;
    }

    s[i] = '\0';

    return i;
}


/* partialcopy: copy a piece of "from" into "to", from positions "a" to "b";
                assume "to" is big enough. */

void partialcopy(char to[], char from[], int a, int b)
{
    int i;

    for(i = a; i <= b; ++i)
        to[i - a] = from[i];

    to[i - a] = '\0';
}
