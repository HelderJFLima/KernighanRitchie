/* Exercise 2-8. Write a function "rightrot(x, n)" that returns the value of the
   integer "x" rotated to the right by "n" positions. */


#include <stdio.h>
#include <ctype.h>      /* Used by "atoi" function */

#define MAXSTR 51       /* Maximum bit string length (one place left for '\0') */

int getline(char line[], int maxline);

unsigned atoi(char string[]);

int binlength(unsigned num);

void inttobit(char string[], unsigned num, int maxstr);

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y);

unsigned rightrot(unsigned x, unsigned n);


main()
{
    unsigned n, x;
    char nstr[MAXSTR];

    printf("\nThis program rotates an integer number ");

    printf("x to the right by n positions.\n");

    printf("\nEnter number x:\n\n");

    if( getline(nstr, MAXSTR) > 0 )
    {
        x = atoi(nstr);

        printf("\nEnter number n:\n\n");

        if( getline(nstr, MAXSTR) > 0 )
        {
            n = atoi(nstr);

            printf("\n\nResults:\n\n%u\n", x);

            inttobit(nstr, x, MAXSTR);      /* Convert to bit string form. */

            printf("%s\n", nstr);

            x = rightrot(x, n);                         /** rightrot test **/

            inttobit(nstr, x, MAXSTR);

            printf("%s\n", nstr);

            printf("%u\n\n", x);
        }
        else
            printf("\nNo number n was given.\n");
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


/* binlength: return the number of bits of a decimal integer. */

int binlength(unsigned n)
{
    int num;
    unsigned p = 1;

    for(num = 0; n >= p; num++)
        p = 2U * p;

    if(num == 0)
        num = 1;

    return num;
}


/* inttobit: convert a decimal value into a string with its equivalent binary
             digits. */

void inttobit(char s[], unsigned n, int lim)
{
    int i, size;

    size = binlength(n);                /* Determine the size of the string. */

    if(size < lim)
    {
        s[size] = '\0';

        for(i = size - 1; i >= 0; i--)  /* Convert to binary form. */
        {
            s[i] = (char)(n % 2U) + '0';

            n = n / 2U;
        }
    }
    else                                /* Overflow case */
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


/* rightrot: return the value of the integer "x" rotated to the right by "n"
             positions. */

unsigned rightrot(unsigned x, unsigned n)
{
    unsigned aux, size;

    size = (unsigned)binlength(x);          /* Number of bits of x */

    n = n % size;

    if(n > 0)
    {
        aux = x & ~(~0 << n);               /* Last n bits of x */

        x = x >> n;

        x = setbits(x, size - 1, n, aux);   /* Put the n bits at the beginning
                                               of x. */
    }

    return x;
}
