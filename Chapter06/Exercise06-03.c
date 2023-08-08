/* Exercise 6-3. Write a cross-referencer that prints a list of all words in a
   document, and for each word, a list of the line numbers on which it occurs.
   Remove noise words like "the", "and" and so on. */


#include <ctype.h>      /* For isalpha, isblank, tolower */
#include <stdio.h>
#include <stdlib.h>     /* For malloc */
#include <string.h>     /* For strcmp, strcpy, strlen */

#define EMPTY   0       /* For getch/ungetch buffer */
#define FULL    1
#define KWNUM   ( sizeof noisewords / sizeof noisewords[0] )
#define MAXWORD 100     /* Maximum size of a word read */


struct treenode
*addtree(struct treenode *ptr, char *word, int linenum);

int getword(char *word, int lim);

int iskeyword(char *word, char *kwords[], int kwnum);

void treeprint(struct treenode *ptr);


char *noisewords[] = { "a", "am", "an", "and", "are", "as", "at", "be", "but",
                       "by", "do", "does", "did", "for", "had", "have", "he",
                       "her", "hers", "him", "his", "i", "if", "in", "is", "it",
                       "its", "me", "mine", "my", "of", "off", "on", "once",
                       "only", "or", "our", "ours", "she", "so", "than", "that",
                       "the", "then", "their", "theirs", "them", "they", "to",
                       "until", "up", "us", "we", "what", "when", "where",
                       "which", "while", "why", "will", "with", "you", "your",
                       "yours" };


/* Node for list with line numbers */

struct listnode { int number;
                  struct listnode *next; };


/* Node for tree with words and line numbers */

struct treenode { char *word;
                  struct listnode *firstnum;
                  struct listnode *lastnum;
                  struct treenode *left;
                  struct treenode *right; };


int buffer;             /* Buffer for getch/ungetch */
int status = EMPTY;     /* Buffer status */


/* print a list of all words in a document, and for each word, a list of the
   line numbers on which it occurs. */

main()
{
    int c, line = 1;
    char word[MAXWORD];
    struct treenode *root = NULL;

    printf("\nEnter a text:\n\n");

    while( ( c = getword(word, MAXWORD) ) != EOF )
    {
        if(c == '\n')
            line++;

        if( isalpha(word[0]) && !iskeyword(word, noisewords, KWNUM) )
            root = addtree(root, word, line);
    }

    printf("\n\nWords and line numbers:\n\n");

    treeprint(root);

    return 0;
}


/* addlist: add a listnode at "p" or at the next node. */

struct listnode
*addlist(struct listnode *p, int num)
{
    struct listnode *lalloc(void);

    if(p == NULL)                       /* New node */
    {
        p = lalloc();

        if(p != NULL)
        {
            p->number = num;

            p->next = NULL;
        }
        else
        {
            printf("\n* lalloc ERROR *: ");

            printf("malloc returned NULL for %d\n\n", num);
        }

        return p;
    }
    else if(p->number < num)            /* If the number is not already there */
    {
        p->next = addlist(p->next, num);

        return p->next;                 /* New last node */
    }
}


/* addtree: add a treenode at or below "p". */

struct treenode
*addtree(struct treenode *p, char *word, int lnum)
{
    int comp;
    char *strdupl(char *);
    struct listnode *addlist(struct listnode *, int);
    struct treenode *talloc(void);

    if(p == NULL)                                   /* New word */
    {
        p = talloc();

        if(p != NULL)
        {
            if( ( p->word = strdupl(word) ) == NULL)
            {
                printf("\n* strdupl ERROR *: ");

                printf("malloc returned NULL for %s\n\n", word);
            }

            p->lastnum = addlist(NULL, lnum);       /* New number list */

            p->firstnum = p->lastnum;

            p->left = p->right = NULL;
        }
        else
        {
            printf("\n* talloc ERROR *: ");

            printf("malloc returned NULL for %s\n\n", word);
        }
    }
    else if( ( comp = strcmp(word, p->word) ) == 0 )

        p->lastnum = addlist(p->lastnum, lnum);     /* Add the line number. */

    else if(comp < 0)                               /* Into left subtree */

        p->left = addtree(p->left, word, lnum);

    else                                            /* Into right subtree */
        p->right = addtree(p->right, word, lnum);

    return p;
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


/* getword: get next word or character from input. */

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while( isblank( c = getch() ) )             /* Skip white spaces. */
        ;

    if(c != EOF)
        *w++ = isalpha(c) ? tolower(c) : c;     /* Only lower case letters */

    if( !isalpha(c) )
    {
        *w = '\0';

        return c;
    }

    for( ; --lim > 0; w++)
    {
        if(!isalpha( *w = tolower( getch() ) ) )
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


/* lalloc: make a listnode. */

struct listnode
*lalloc(void)
{
    return (struct listnode *)malloc( sizeof(struct listnode) );
}


/* listprint: print the list "p". */

void listprint(struct listnode *p)
{
    if(p != NULL)
    {
        printf("%d ", p->number);

        listprint(p->next);
    }
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


/* talloc: make a treenode. */

struct treenode
*talloc(void)
{
    return (struct treenode *)malloc( sizeof(struct treenode) );
}


/* treeprint: in-order print of tree "p". */

void treeprint(struct treenode *p)
{
    void listprint(struct listnode *);

    if(p != NULL)
    {
        treeprint(p->left);

        printf("%s:   ", p->word);

        listprint(p->firstnum);

        printf("\n");

        treeprint(p->right);
    }
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
