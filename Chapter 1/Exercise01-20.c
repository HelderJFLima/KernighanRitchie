/* Exercise 1-20. Write a program "detab" that replaces tabs in the input
   with the proper number of blanks to space to the next tab stop. Assume
   a fixed set of tab stops, say every n columns. Should n be a variable
   or a symbolic parameter? */

#include <stdio.h>

#define TAB 4   /* Number of columns in a tab */

main()          /* detab: replace tabs in the input with the proper number of blanks */
{
    int c, i, n, pos;

    pos = 0;                                /* Position in the line */

    printf("\nEnter a text:\n\n");

    while( (c = getchar()) != EOF )
    {
        if(c != '\t')
        {
            putchar(c);

            ++pos;

            if(c == '\n')                   /* 'pos' starts to be counted on each new line. */
                pos = 0;
        }
        else                                /* Replace a tab. */
        {
            n = TAB - ( pos - (pos / TAB) * TAB );      /* Number of spaces to put in the line */

            for(i = 0; i < n; ++i)
            {
                putchar(' ');

                ++pos;
            }
        }
    }

    return 0;
}
