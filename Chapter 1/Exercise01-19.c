/* Exercise 1-19. Write a function "reverse(s)" that reverses the character string s.
   Use it to write a program that reverses its input a line at a time. */

#include <stdio.h>

#define MAXLINE 1000    /* Maximum input line length */

int getline(char line[], int maxline);

void reverse(char string[]);

main()                  /* Reverses its text input a line at a time */
{
    char line[MAXLINE];     /* Current input line */

    printf("\nEnter lines of text:\n\n");

    while( getline(line, MAXLINE) > 0 )
    {
        reverse(line);

        printf("%s\n\n", line);
    }

    return 0;
}

int getline(char s[], int lim)      /* Read a line into "s"; return length. */
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

void reverse(char s[])      /* Reverse the character string "s". */
{
    char temp;
    int i;
    int last;       /* Position of the last character to exchange */

    for(last = 0; s[last] != '\0'; ++last)  /* Find the last valid position. */
        ;

    --last;

    for(i = 0; i < last; ++i)               /* Exchange characters. */
    {
        temp = s[i];

        s[i] = s[last];

        s[last] = temp;

        --last;
    }
}
