/* Exercise 6-6. Implement a simple version of the #define processor (i.e., no
   arguments) suitable for use with C programs, based on the routines of this
   section. You may also find "getch" and "ungetch" helpful. */


/* This is just a stupid draft */


#include <ctype.h>      /* For isalnum, isspace */
#include <stdio.h>
#include <stdlib.h>     /* For malloc */
#include <string.h>     /* For strcmp, strcpy, strlen */

#define EMPTY    0      /* For getch/ungetch buffer */
#define FULL     1
#define HASHSIZE 101
#define MAXWORD  100    /* Maximum size of a word read */


int getword(char *word, int lim);

struct nlist
*install(char *name, char *defn);


/* Table entry */

struct nlist { char *name;                  /* Defined name */
               char *defn;                  /* Replacement text */
               struct nlist *next; };       /* Next entry in chain */


int buffer;                                 /* Buffer for getch/ungetch */
int status = EMPTY;                         /* Buffer status */
static struct nlist *hashtab[HASHSIZE];     /* Pointer table */


/* Read input and put preprocessor names and definitions in a table. */

main()
{
    int c, i;
    char word1[MAXWORD], word2[MAXWORD];

    for(i = 0; i < HASHSIZE; i++)
        hashtab[i] = NULL;

    while( ( c = getword(word1, MAXWORD) ) != EOF )    /* Get words. */
    {
        if(strcmp(word1, "#define") == 0)
        {
            getword(word1, MAXWORD);

            getword(word2, MAXWORD);

            install(word1, word2);
        }
    }

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


/* getword: get next word or character from input; ignore comments, strings and
            char constants. */

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while ( isspace( c = getch() ) )                /* Jump spaces. */
        ;

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

    if(!isalnum(c) && c != '_' && c != '#')
    {
        *w = '\0';

        return c;
    }

    for( ; --lim > 0; w++)
    {
        if(!isalnum( *w = getch() ) && *w != '_' && *w != '#')
        {
            ungetch(*w);

            break;
        }
    }

    *w = '\0';

    return word[0];
}


/* hash: form hash value for string "s". */

unsigned hash(char *s)
{
    unsigned hashval;

    for(hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}


/* install: put (name, defn) in hashtab. */

struct nlist
*install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    unsigned hash(char *);
    struct nlist *lookup(char *);
    char *strdupl(char *);

    if( ( np = lookup(name) ) == NULL )     /* Not found */
    {
        np = (struct nlist *)malloc( sizeof(struct nlist) );

        if (np == NULL || ( np->name = strdupl(name) ) == NULL)
            return NULL;

        hashval = hash(name);

        np->next = hashtab[hashval];

        hashtab[hashval] = np;
    }
    else                                    /* Already there */
        free( (void *) np->defn );              /*Free previous defn. */

    if ( ( np->defn = strdup(defn) ) == NULL )
        return NULL;

    return np;
}


/* lookup: look for "s" in hashtab. */

struct nlist
*lookup(char *s)
{
    struct nlist *np;
    unsigned hash(char *);

    for(np = hashtab[ hash(s) ]; np != NULL; np = np->next)
    {
        if(strcmp(s, np->name) == 0)                           /* Found */
            return np;
    }

    return NULL;                                                /* Not found */
}


/* strdupl: make a duplicate of "str". */

char *strdupl(char *str)
{
    char *p;

    p = (char *)malloc(strlen(str) + 1);

    if(p != NULL)
        strcpy(p, str);

    return p;
}


/* ungetch: push character back on input. */

void ungetch(int c)
{
    if(status == EMPTY)
    {
        buffer = c;

        status = FULL;
    }
    else
        printf("\n* ungetch ERROR *: buffer overflow\n\n");
}
