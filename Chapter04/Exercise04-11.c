/* Exercise 4-11. Modify "getop" so that it doesn't need to use "ungetch".
   Hint: use an internal static variable. */


#include <ctype.h>

#define BUFSIZE 100


/* getop: get next character or numeric operand. */

int getop(char s[])
{
    int i, c;
    static int bufp = 0;           /* Next free position in buf */
    static char buf[BUFSIZE];      /* Buffer */

    while ( ( s[0] = c = (bufp > 0) ? buf[--bufp] : getchar() ) == ' ' ||
             c == '\t' )
        ;

    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;                                   /* Not a number */

    i = 0;

    if (isdigit(c))                                 /* Collect integer part */
        while ( isdigit( s[++i] = c = (bufp > 0) ? buf[--bufp] : getchar() ) )
            ;

    if (c == '.')                                   /* Collect fraction part */
        while ( isdigit( s[++i] = c = (bufp > 0) ? buf[--bufp] : getchar() ) )
            ;

    s[i] = '\0';

    if (c != EOF)
    {
        if (bufp >= BUFSIZE)
            printf("ungetch: too many characters\n");

        else
            buf[bufp++] = c;
    }

    return NUMBER;
}
