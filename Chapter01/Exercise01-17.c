/* Exercise 1-17. Write a program to print all input lines that are longer than
   80 characters. */


#include <stdio.h>

#define MAXLINE 1000        /* Maximum input line length */
#define MINLIMIT 80         /* Minimum limit of line length */

int getline(char line[], int maxline);


/* Print all input lines that are longer than MINLIMIT characters. */

main()
{
    int len;                /* Current line length */
    char line[MAXLINE];     /* Current input line */

    printf("\nEnter phrases:\n\n");

    while( (len = getline(line, MAXLINE)) > 0 )
        if(len > MINLIMIT)
            printf("\nLonger than %d characters: %s\n", MINLIMIT, line);

    return 0;
}


/* getline: read a line into "s"; return length. */

int getline(char s[],int lim)
{
    int c, i;

    for (i=0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if(c == '\n')
    {
        s[i] = c;

        ++i;
    }

    s[i] = '\0';

    return i;
}
