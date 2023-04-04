/* Exercise 2-6. Write a function "setbits(x, p, n, y)" that returns "x" with
   the "n" bits that begin at position "p" set to the rightmost "n" bits of "y",
   leaving the other bits unchanged. */


#include <stdio.h>
#include <ctype.h>      /* Used by "atoi" function */

#define MAXSTR 51       /* Maximum bit string length (one place left for '\0') */

int getline(char line[], int maxline);

unsigned atoi(char string[]);

void inttobit(char string[], unsigned num, int maxstr);

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y);


main()
{
    unsigned n, p, x, y;
    char nstr[MAXSTR];

    printf("\nThis program reads four positive integer numbers x, p, n, y ");

    printf("and returns x with the n bits\nthat begin at position p set to ");

    printf("the rightmost n bits of y, leaving the other bits unchanged.\n");

    printf("\nEnter number x:\n\n");

    if( getline(nstr, MAXSTR) > 0 )
    {
        x = atoi(nstr);

        printf("\nEnter number p:\n\n");

        if( getline(nstr, MAXSTR) > 0 )
        {
            p = atoi(nstr);

            printf("\nEnter number n:\n\n");

            if( getline(nstr, MAXSTR) > 0 )
            {
                n = atoi(nstr);

                printf("\nEnter number y:\n\n");

                if( getline(nstr, MAXSTR) > 0 )
                {
                    y = atoi(nstr);

                    inttobit(nstr, x, MAXSTR);  /* Convert to bit string form. */

                    printf("\n\nResults:\n\n%s\n", nstr);

                    inttobit(nstr, y, MAXSTR);

                    printf("%s\n", nstr);

                    x = setbits(x, p, n, y);                /** setbits test **/

                    inttobit(nstr, x, MAXSTR);

                    printf("%s\n\n", nstr);
                }
                else
                    printf("\nNo number y was given.\n");
            }
            else
                printf("\nNo number n was given.\n");
        }
        else
            printf("\nNo number p was given.\n");
    }
    else
        printf("\nNo number x was given.\n");

    return 0;
}


/* getline: read a line into "s"; return length. */

int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if(c == '\n')
    {
        s[i] = c;

        ++i;
    }

    s[i] = '\0';

    return i;
}


/* atoi: convert a string of decimal digits into its equivalent integer value. */

unsigned atoi(char s[])
{
    int i;
    unsigned n = 0;

    for(i = 0; isdigit(s[i]); i++)
        n = 10U * n + (unsigned)(s[i] - '0');

    return n;
}


/* inttobit: convert a decimal value into a string with its equivalent binary
             digits. */

void inttobit(char s[], unsigned n, int lim)
{
    int i, size;
    unsigned p = 1;

    for(size = 0; n >= p; size++)           /* Determine the size of the string. */
        p = 2U * p;

    if(size > 0 && size < lim)
    {
        s[size] = '\0';

        for(i = size - 1; i >= 0; i--)      /* Convert to binary form. */
        {
            s[i] = (char)(n % 2U) + '0';

            n = n / 2U;
        }
    }
    else if(size == 0 && lim >= 2)          /* Zero value */
    {
        s[0] = '0';

        s[1] = '\0';
    }
    else                                    /* Overflow case */
        s[0] = '\0';
}


/* setbits: return "x" with the "n" bits that begin at position "p" set to the
            rightmost "n" bits of "y", leaving the other bits unchanged. */

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y)
{
    unsigned mask;

    mask = ~(~0 << n);

    y = y & mask;                   /* Select the n rightmost bits of y. */

    mask = ~( mask << (p - n + 1U) );

    y = y << (p - n + 1U);          /* Set the n bits in the right position. */

    x = (x & mask) | y;             /* Swap the n bits of x for those of y. */

    return x;
}
