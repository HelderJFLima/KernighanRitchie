/* Exercise 5-2. Write "getfloat", the floating-point analog of "getint". What
   type does "getfloat" return as its function value? */


/* This function returns EOF for end of file, zero if the next input is not a
   number, and a positive value if the input contains a valid number. */


#include <ctype.h>

int getch(void);

void ungetch(int);


/* getfloat: get next floating-point number from input into "*pn". */

int getfloat(double *pn)
{
    int c, sign;
    double power;

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
        *pn = 0.0;
    else
        *pn = -1.0;

    while( isdigit(c) )
    {
        *pn = 10.0 * (*pn) + (double)(c - '0');

        c = getch();
    }

    if(c == '.')
        c = getch();

    power = 1.0;

    while( isdigit(c) )
    {
        *pn = 10.0 * (*pn) + (double)(c - '0');

        power *= 10.0;

        c = getch();
    }

    if(*pn >= 0)                            /* Number */
    {
        *pn = (double)sign * (*pn) / power;

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
