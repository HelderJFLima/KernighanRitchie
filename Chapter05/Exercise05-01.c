/* Exercise 5-1. As written, "getint" treats a "+" or "-" not followed by a
   digit as a valid representation of zero. Fix it to push such a character
   back on the input. */


#include <ctype.h>

int getch(void);

void ungetch(int);


/* getint: get next integer from input into "*pn". */

int getint(int *pn)
{
    int c, sign;

    while( isspace( c = getch() ) )         /* Skip white spaces */
        ;

    if(!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);                         /* It is not a number */

        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if(c == '+' || c == '-')
        c = getch();

    if( isdigit(c) )
        *pn = 0;
    else
        *pn = -1;

    while( isdigit(c) )
    {
        *pn = 10 * (*pn) + (c - '0');

        c = getch();
    }

    if(*pn >= 0)                            /* Number */
    {
        *pn *= sign;

        if(c != EOF)
            ungetch(c);

        return c;
    }
    else if(c == EOF)                       /* EOF */

        return c;

    else                                    /* Not a number */
    {
        ungetch(c);

        return 0;
    }
}
