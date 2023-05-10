/* Exercise 4-9. Our "getch" and "ungetch" do not handle a pushed-back "EOF"
   correctly. Decide what their properties ought to be if an "EOF" is pushed
   back, then implement your design. */


/* The only difference is that "buf" is an array of int instead of char. */


#define BUFSIZE 100

int buf[BUFSIZE];       /* Buffer for "ungetch" */
int bufp = 0;           /* Next free position in "buf" */


/* getch: get a (possibly pushed-back) character. */

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}


/* ungetch: push character back on input. */

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
