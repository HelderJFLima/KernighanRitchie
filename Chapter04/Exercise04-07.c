/* Exercise 4-7. Write a routine "ungets(s)" that will push back an entire
   string onto the input. Should "ungets" know about "buf" and "bufp", or
   should it just use "ungetch"? */


/* Just the function */


#include <string.h>

#define BUFSIZE 100

char buf[BUFSIZE];      /* Buffer for "ungets" */
int bufp = 0;           /* Next free position in "buf" */


/* ungets: push character string back on input. */

void ungets(char s[])
{
    int i;

    if (strlen(s) > BUFSIZE - bufp)
        printf("ungets: too many characters\n");
    else
    {
        for(i = strlen(s) - 1; i >= 0; i--)
            buf[bufp++] = s[i];
    }
}
