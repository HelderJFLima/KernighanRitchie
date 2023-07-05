/* Exercise 5-6. Rewrite appropriate programs from earlier chapters and
   exercises with pointers instead of array indexing. Good possibilities
   include "getline" (Chapters 1 and 4), "atoi", "itoa", and their variants
   (Chapters 2, 3, and 4), "reverse" (Chapter 3), and "strindex" and "getop"
   (Chapter 4). */


/* I did all the suggestions except "getop", because
   I didn't like "getop"... u.u */


#include <ctype.h>      /* Used by "atoi" function */
#include <limits.h>     /* Used by "itoa" function */
#include <stdio.h>

#define MAXSTR 1000     /* Maximum string size */

int atoi(char string[]);

int getline(char line[], int maxline);

void itoa(int num, char str[]);

void reverse(char str[]);

int strindex(char source[], char searchfor[]);

char pattern[] = "123";


main()
{
    int n, p;
    char str1[MAXSTR], str2[MAXSTR];

    printf("\nEnter an integer number:\n\n");

    if( getline(str1, MAXSTR) > 0 )
    {
        n = atoi(str1);

        itoa(n, str2);

        p = strindex(str1, pattern);

        printf("\n\n%s\n%d\n\n%s\n\n%d\n", str1, n, str2, p);

        reverse(str2);

        printf("\n%s\n", str2);
    }

    return 0;
}


/* atoi: convert a string of decimal digits into its equivalent integer value;
         pointer version. */

int atoi(char *s)
{
    int sign, n = 0;

    while( isblank(*s) )                /* Jump blanks. */
        s++;

    sign = (*s == '-') ? -1 : 1;

    if(*s == '-' || *s == '+')
        s++;

    while( isdigit(*s) )
          n = 10 * n + (int)(*s++ - '0');

    return sign * n;
}


/* getline: read a line into "s"; return length; pointer version */

int getline(char *s, int lim)
{
    int c, n = 0;

    while(lim - 1 > 0 && (c = getchar()) != EOF && c != '\n')
    {
        *s++ = c;

        lim--;

        n++;
    }

    if(c == '\n')
    {
        *s++ = c;

        n++;
    }

    *s = '\0';

    return n;
}


/* itoa: convert "n" to characters in "s"; pointer version. */

void itoa(int n, char *s)
{
    int sign;
    char *ss = s;

    if( (sign = n) < 0 && n == INT_MIN )    /* Largest negative number case */
    {                                       /* Record sign. */
        n++;

        n = -n;                             /* Make n positive. */

        *ss++ = n % 10 + '0' + 1;           /* Handle the last digit. */

        n /= 10;
    }
    else if(sign < 0)
        n = -n;

    do                                      /* Generate digits in reverse */
    {                                       /* order. */

        *ss++ = n % 10 + '0';               /* Get next digit. */

    } while ( (n /= 10) > 0 );              /* Delete it. */

    if (sign < 0)
        *ss++ = '-';

    *ss = '\0';

    reverse(s);
}


/* reverse: reverse string "s" in place; pointer version. */

void reverse(char *s)
{
    int c;
    char *sa, *sb;

    sa = sb = s;

    while(*sb != '\0')
        sb++;

    if(sb > sa)
        sb--;

    while(sa < sb)
    {
        c = *sa;

        *sa++ = *sb;

        *sb-- = c;
    }
}


/* strindex: return index of "t" in "s", or -1 if there is none;
             pointer version. */

int strindex(char *s, char *t)
{
    char *sa, *sb, *tt;

    sa = s;

    while(*sa != '\0')
    {
        sb = sa;

        tt = t;

        while(*tt != '\0' && *sb == *tt)
            sb++, tt++;

        if(tt > t && *tt == '\0')
            return sa - s;

        sa++;
    }

    return -1;
}
