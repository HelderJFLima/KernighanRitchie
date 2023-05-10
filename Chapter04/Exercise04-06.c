/* Exercise 4-6. Add commands for handling variables. (It's easy to provide
   twenty-six variables with single-letter names.) Add a variable for the most
   recently printed value. */


/* Extremely simple pseudo solution. The exercise is too vague. */


#include <stdio.h>
#include <stdlib.h>     /* For "atof" */

#define MAXOP 100       /* Max size of operand or operator */
#define NUMBER '0'      /* Signal that a number was found */

int getop(char []);

double pop(void);

void push(double);

double a, b, c, d, e, rec;      /* Variables */


/* Reverse Polish calculator */

main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ( (type = getop(s)) != EOF )
    {
        switch (type)
        {
            case NUMBER:
                push( atof(s) );

                break;

            case '+':
                push( pop() + pop() );

                break;

            case '*':
                push( pop() * pop() );

                break;

            case '-':
                op2 = pop();

                push( pop() - op2);

                break;

            case '/':
                op2 = pop();

                if (op2 != 0.0)
                    push( pop() / op2);
                else
                    printf("error: zero divisor\n");

                break;

            case '%':                                       /** Modulus **/
                op2 = pop();

                if (op2 != 0.0)
                    push( (int)pop() % (int)op2 );

                else
                    printf("error: zero divisor\n");

                break;

            case 'a':
                a = pop();

                push(a);

                break;

            case 'b':
                b = pop();

                push(b);

                break;

            case 'c':
                c = pop();

                push(c);

                break;

            case 'd':
                d = pop();

                push(d);

                break;

            case 'e':
                e = pop();

                push(e);

                break;

            case '\n':
                op2 = pop();

                printf("\t%.8g\n", op2 );

                rec = op2;

                break;

            default:
                printf("error: unknown command %s\n", s);

                break;
        }
    }

    return 0;
}


#define MAXVAL 100      /* Maximum depth of val stack */

int sp = 0;             /* Next free stack position */
double val[MAXVAL];     /* Value stack */


/* push: push "f" onto value stack. */

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}


/* pop: pop and return top value from stack. */

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");

        return 0.0;
    }
}


#include <ctype.h>

int getch(void);

void ungetch(int);


/* getop: get next character or numeric operand. */

int getop(char s[])
{
    int i, c;

    while ( (s[0] = c = getch()) == ' ' || c == '\t' )
        ;

    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;                                   /* Not a number */

    i = 0;

    if (isdigit(c))                                 /* Collect integer part. */
        while ( isdigit( s[++i] = c = getch() ) )
            ;

    if (c == '.')                                   /* Collect fraction part. */
        while ( isdigit( s[++i] = c = getch() ) )
            ;

    s[i] = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
}


#define BUFSIZE 100

char buf[BUFSIZE];      /* Buffer for "ungetch" */
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
