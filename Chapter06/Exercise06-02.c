/* Exercise 6-2. Write a program that reads a C program and prints in
   alphabetical order each group of variable names that are identical in the
   first 6 characters, but different somewhere thereafter. Don't count words
   within strings and comments. Make "6" a parameter that can be set from the
   command line. */


#include <ctype.h>      /* For isalnum, isalpha, isdigit, isspace */
#include <stdio.h>
#include <stdlib.h>     /* For malloc */
#include <string.h>     /* For strcmp, strcpy, strlen, strncmp, strncpy */

#define EMPTY   0       /* For getch/ungetch buffer */
#define FULL    1
#define KWNUM   ( sizeof keywords / sizeof keywords[0] )
#define MAXARG  10      /* Maximum size of an argument */
#define MAXWORD 100     /* Maximum size of a word read */
#define N       6       /* Default value of argument "-n" */


struct labelnode
*addlabeltree(struct labelnode *ptr, char *var, int lsize);

struct varnode
*addvartree(struct varnode *ptr, char *var);

int getword(char *word, int lim);

int iskeyword(char *word, char *kwords[], int kwnum);

void ltreeprint(struct labelnode *ptr);

int readarg(int *argint, char *argch[]);

void vtreeprint(struct varnode *ptr);


char *keywords[] = { "auto", "break", "case", "char", "const", "continue",
                     "default", "do", "double", "else", "enum", "extern",
                     "float", "for", "goto", "if", "int", "long", "register",
                     "return", "short", "signed", "sizeof", "static", "struct",
                     "switch", "typedef", "union", "unsigned", "void",
                     "volatile", "while" };


/* Node for tree with variable names */

struct varnode { char *varname;
                 struct varnode *left;
                 struct varnode *right; };


/* Node for tree with groups of variables */

struct labelnode { char *label;
                   struct varnode *vars;        /* Tree with variable names */
                   struct labelnode *left;
                   struct labelnode *right; };


int buffer;             /* Buffer for getch/ungetch */
int status = EMPTY;     /* Buffer status */


/* Read and print groups of variable names in alphabetical order. */

main(int argc, char *argv[])
{
    int n;
    char word[MAXWORD];
    struct labelnode *root1;
    struct varnode *root2;

    if(argc == 2)                   /* From argument */
    {
        if( !readarg(&n, argv) )
            return 1;
    }
    else if(argc == 1)              /* No argument */

        n = N;

    else
    {
        printf("\n* ERROR *: invalid number of arguments\n\n");

        return 2;
    }

    root1 = root2 = NULL;

    while (getword(word, MAXWORD) != EOF)
    {
        if (word[0] == '_' ||
            isalpha(word[0]) && !iskeyword(word, keywords, KWNUM) )
        {
            if(strlen(word) >= n)

                root1 = addlabeltree(root1, word, n);   /* Main tree */

            else
                root2 = addvartree(root2, word);        /* Secondary tree */
        }
    }

    printf("\nVariable names:\n\n");

    if(root1 == NULL && root2 == NULL)
        printf("\nNONE\n\n");

    vtreeprint(root2);

    ltreeprint(root1);

    return 0;
}


/* addlabeltree: add a labelnode at or below "p". */

struct labelnode
*addlabeltree(struct labelnode *p, char *var, int lsize)
{
    int comp;
    char *strndup(char *, int);
    struct labelnode *lalloc(void);

    if(p == NULL)                                   /* New label */
    {
        p = lalloc();

        if(p != NULL)
        {
            p->label = strndup(var, lsize);

            p->vars = addvartree(NULL, var);        /* New variable */

            p->left = p->right = NULL;
        }
        else
        {
            printf("\n* lalloc ERROR *: ");

            printf("malloc returned NULL for %s\n\n", var);
        }
    }
    else if( ( comp = strncmp(var, p->label, lsize) ) == 0)

        p->vars = addvartree(p->vars, var);         /* Add the variable name. */

    else if(comp < 0)                               /* Into left subtree */

        p->left = addlabeltree(p->left, var, lsize);

    else                                            /* Into right subtree */
        p->right = addlabeltree(p->right, var, lsize);

    return p;
}


/* addvartree: add a varnode at or below "p". */

struct varnode
*addvartree(struct varnode *p, char *var)
{
    int comp;
    char *strdup(char *);
    struct varnode *valloc(void);

    if(p == NULL)                                       /* New variable */
    {
        p = valloc();

        if(p != NULL)
        {
            p->varname = strdup(var);

            p->left = p->right = NULL;
        }
        else
        {
            printf("\n* valloc ERROR *: ");

            printf("malloc returned NULL for %s\n\n", var);
        }
    }
    else if( ( comp = strcmp(var, p->varname) ) < 0)    /* Into left subtree */

        p->left = addvartree(p->left, var);

    else if(comp > 0)                                   /* Into right subtree */

        p->right = addvartree(p->right, var);

    return p;
}


/* copyarg: copy an argument to an array; return 0 if there is any problem with
            the argument and 1 otherwise. */

int copyarg(char num[], char arg[])
{
    int i = 0;

    while(*arg != '\0')
    {
        if(isdigit(*arg) && i < MAXARG - 1)

            num[i++] = *arg++;

        else
            return 0;
    }

    num[i] = '\0';

    if(i > 0)

        return 1;

    else
        return 0;
}


/* getch: get a (possibly pushed-back) character. */

int getch(void)
{
    if(status == FULL)
    {
        status = EMPTY;

        return buffer;
    }
    else
        return getchar();
}


/* getword: get next word or character from input; ignore preprocessor control
            lines, comments, strings and char constants. */

int getword(char *word, int lim)
{
    int c, cont, getch(void);
    void ungetch(int);
    char *w = word;

    while ( isspace( c = getch() ) )                /* Jump spaces. */
        ;

    if(c == '#')                                    /* Jump preprocessor */
    {                                               /* control lines. */
        cont = 0;

        while( ( c = getch() ) != EOF )
        {
            if(c == '\\')
                cont = 1;

            if(c == '\n' && !cont)
            {
                c = getch();

                break;
            }
            else if(c == '\n')
                cont = 0;
        }
    }

    if(c == '\\')
    {
        if( ( c = getch() ) == '*' )                /* Jump comments. */
        {
            while( ( c = getch() ) != EOF )
            {
                if(c == '*')
                {
                    if( ( c = getch() ) == '/' )
                    {
                        c = getch();

                        break;
                    }
                    else
                        ungetch(c);
                }
            }
        }
        else
        {
            ungetch(c);

            *w++ = '\\';

            *w = '\0';

            return '\\';
        }
    }

    if(c == '\"')                                   /* Jump strings. */
    {
        while( ( c = getch() ) != EOF )
        {
            if(c == '\"')
            {
                c = getch();

                break;
            }
        }
    }

    if(c == '\'')                                   /* Jump char constants. */
    {
        while( ( c = getch() ) != EOF )
        {
            if(c == '\'')
            {
                c = getch();

                break;
            }
        }
    }

    if(c != EOF)
        *w++ = c;

    if(!isalpha(c) && c != '_')
    {
        *w = '\0';

        return c;
    }

    for( ; --lim > 0; w++)
    {
        if(!isalnum( *w = getch() ) && *w != '_')
        {
            ungetch(*w);

            break;
        }
    }

    *w = '\0';

    return word[0];
}


/* iskeyword: check if a word is in a keyword list. */

int iskeyword(char *word, char *kword[], int kwnum)
{
    int i, match = 0;

    for(i = 0; i < kwnum; i++)
    {
        if(strcmp(word, kword[i]) == 0)
        {
            match = 1;

            break;
        }
    }

    return match;
}


/* lalloc: make a labelnode. */

struct labelnode
*lalloc(void)
{
    return (struct labelnode *)malloc( sizeof(struct labelnode) );
}


/* ltreeprint: in-order print of labelnode tree "p". */

void ltreeprint(struct labelnode *p)
{
    if(p != NULL)
    {
        ltreeprint(p->left);

        printf("\n");

        vtreeprint(p->vars);

        ltreeprint(p->right);
    }
}


/* readarg: read an argument and convert it to an integer; return 0 if there is
            some error and 1 otherwise.*/

int readarg(int *argint, char *argch[])
{
    int copyarg(char *, char *);
    char num[MAXARG];

    if(*++argch != NULL)                    /* If there is an argument */
    {
        if(**argch == '-')                  /* Argument "-n" */
        {
            if( copyarg(num, *argch + 1) )  /* Copy and convert to integer. */

                *argint = atoi(num);

            else
            {
                printf("\n* ERROR *: invalid argument: %s\n\n", *argch);

                return 0;
            }
        }
        else
        {
            printf("\n* ERROR *: unknown argument: %s\n\n", *argch);

            return 0;
        }

        return 1;
    }
    else
    {
        printf("\n* ERROR *: no argument given.\n\n");

        return 0;
    }
}


/* strdup: make a duplicate of "str". */

char *strdup(char *str)
{
    char *p;

    p = (char *)malloc(strlen(str) + 1);

    if(p != NULL)
        strcpy(p, str);

    return p;
}


/* strndup: make a duplicate of the first n characters of "str". */

char *strndup(char *str, int n)
{
    char *p;

    p = (char *)malloc(n + 1);

    if(p != NULL)
        strncpy(p, str, n);

    p[n] = '\0';

    return p;
}


/* ungetch: push character back on input. */

void ungetch(int c)
{
    if (status == EMPTY)
    {
        buffer = c;

        status = FULL;
    }
    else
        printf("\n* ungetch ERROR *: buffer overflow\n\n");
}


/* valloc: make a varnode. */

struct varnode
*valloc(void)
{
    return (struct varnode *)malloc( sizeof(struct varnode) );
}


/* vtreeprint: in-order print of varnode tree "p". */

void vtreeprint(struct varnode *p)
{
    if(p != NULL)
    {
        vtreeprint(p->left);

        printf("%s\n", p->varname);

        vtreeprint(p->right);
    }
}
