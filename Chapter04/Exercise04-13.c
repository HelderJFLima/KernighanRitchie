/* Exercise 4-13. Write a recursive version of the function "reverse(s)", which
   reverses the string "s" in place. */


#include <stdio.h>
#include <string.h>         /* For "strlen" */

#define MAXLINE 1000        /* Maximum string size */

int getline(char line[], int maxline);

void reverse(char str[], int a, int b);


main()
{
    char str[MAXLINE];

    printf("\nEnter strings:\n\n");

    while( getline(str, MAXLINE) > 0 )
    {
        reverse( str, 0, strlen(str) - 1 );

        printf("%s\n\n\n", str);                        /** reverse test **/
    }

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


/* reverse: reverse string "s" from "a" to "b" in place; recursive version. */

void reverse(char s[], int a, int b)
{
    int c;

    if(a >= 0 && b >= 0)
    {
        if(b > a + 1)
            reverse(s, a + 1, b - 1);           /* Recursion */

        c = s[a];

        s[a] = s[b];

        s[b] = c;
    }
}
