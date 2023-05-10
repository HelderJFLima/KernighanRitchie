/* Exercise 4-8. Suppose that there will never be more than one character of
   pushback. Modify "getch" and "ungetch" accordingly. */


/* Just the functions */


#define FULL 1
#define EMPTY 0


char buf;               /* Buffer for "ungetch" */
int status = EMPTY;     /* Buffer status */


/* getch: get a (possibly pushed-back) character. */

int getch(void)
{
    if(status == FULL)
    {
        status = EMPTY;

        return buf;
    }
    else
        return getchar();
}


/* ungetch: push character back on input. */

void ungetch(int c)
{
    if (status == FULL)
        printf("ungetch: too many characters\n");
    else
    {
        buf = c;

        status = FULL;
    }
}
