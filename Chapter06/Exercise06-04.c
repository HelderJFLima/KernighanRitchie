/* Exercise 6-4. Write a program that prints the distinct words in its input
   sorted into decreasing order of frequency of occurrence. Precede each word
   by its count. */


#include <ctype.h>      /* For isalpha, isblank, tolower */
#include <stdio.h>
#include <stdlib.h>     /* For malloc */
#include <string.h>     /* For strcmp, strcpy, strlen */

#define EMPTY   0       /* For getch/ungetch buffer */
#define FULL    1
#define MAXWORD 100     /* Maximum size of a word read */


struct tnode
*addtree(struct tnode *ptr, char *word);

struct tnode
**aralloc(int num);

int getword(char *word, int lim);

void qsortt(void *arr[], int left, int right,
            int (*comp)(const void *, const void *) );

int reversecmp(struct tnode *a, struct tnode *b);

void treetoarray(struct tnode **arr, struct tnode *tr);

void wordprint(struct tnode **arr, int num);


struct tnode { char *word;
               int count;
               struct tnode *left;
               struct tnode *right; };

int buffer;             /* Buffer for getch/ungetch */
int status = EMPTY;     /* Buffer status */
int wnum = 0;           /* Number of words read */


/* print distinct words in the input sorted into decreasing order of frequency
   of occurrence. */

main()
{
    int c;
    char word[MAXWORD];
    struct tnode *root = NULL;
    struct tnode **arr;

    printf("\nEnter a text:\n\n");

    while( ( c = getword(word, MAXWORD) ) != EOF )      /* Get words. */
    {
        if( isalpha(word[0]) )
            root = addtree(root, word);
    }

    if(root != NULL)

        arr = aralloc(wnum);            /* Make an array to sort the words. */

    else
    {
        printf("\n* ERROR *: no words saved\n\n");

        return 1;
    }

    if(arr != NULL)

        treetoarray(arr, root);                         /* Fill the array. */

    else
    {
        printf("\n* aralloc ERROR *: malloc returned NULL\n\n");

        return 2;
    }

    qsortt( (void**)arr, 0, wnum - 1,                   /* Sort the words. */
            ( int (*)(const void*, const void*) )reversecmp );

    printf("\n\ncount   words\n\n");

    wordprint(arr, wnum);                               /* Print the words. */

    return 0;
}


/* addtree: add a tnode at or below "p". */

struct tnode
*addtree(struct tnode *p, char *word)
{
    int comp;
    char *strdupl(char *);
    struct tnode *talloc(void);

    if(p == NULL)                                       /* New word */
    {
        p = talloc();

        if(p != NULL)
        {
            if( ( p->word = strdupl(word) ) == NULL)
            {
                printf("\n* strdupl ERROR *: ");

                printf("malloc returned NULL for %s\n\n", word);
            }

            p->count = 1;

            p->left = p->right = NULL;

            wnum++;
        }
        else
        {
            printf("\n* talloc ERROR *: ");

            printf("malloc returned NULL for %s\n\n", word);
        }
    }
    else if( ( comp = strcmp(word, p->word) ) == 0 )

        p->count++;                                     /* Repeated word */

    else if(comp < 0)                                   /* Into left subtree */

        p->left = addtree(p->left, word);

    else                                                /* Into right subtree */
        p->right = addtree(p->right, word);

    return p;
}


/* aralloc: make an array of pointers to tnodes. */

struct tnode
**aralloc(int num)
{
    if(num > 0)

        return (struct tnode **)malloc( num * sizeof(struct tnode *) );

    else
        return NULL;
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


/* qsortt: sort "v" elements into increasing order. */

void qsortt(void *v[], int left, int right,
            int (*comp)(const void *, const void *) )
{
    int i, last;
    void swap(void *arr[], int i, int j);

    if(left >= right)       /* Do nothing if array contains fewer than two */
        return;             /* elements. */

    swap(v, left, (left + right) / 2);

    last = left;

    for(i = left + 1; i <= right; i++)
    {
        if( (*comp)( v[i], v[left] ) < 0 )
            swap(v, ++last, i);
    }

    swap(v, left, last);

    qsortt(v, left, last - 1, ( int (*)(const void*, const void*) )comp);

    qsortt(v, last + 1, right, ( int (*)(const void*, const void*) )comp);
}


/* reversecmp: compare the word count in node "a" with that of node "b" in
               reverse order; return <0 if a > b, 0 if a == b, or >0 if a < b. */

int reversecmp(struct tnode *a, struct tnode *b)
{
    if(a->count > b->count)

        return -1;

    else if(a->count == b->count)

        return strcmp(a->word, b->word);    /* Alphabetical order in this case */

    else
        return 1;
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


/* swap: swap two pointers in "v". */

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];

    v[i] = v[j];

    v[j] = temp;
}


/* talloc: make a tnode. */

struct tnode
*talloc(void)
{
    return (struct tnode *)malloc( sizeof(struct tnode) );
}


/* treetoarray: copy the pointers from tnodes to an array. */

void treetoarray(struct tnode **arr, struct tnode *tr)
{
    static int i;               /* Automatically initialized to zero */

    if(tr != NULL)
    {
        treetoarray(arr, tr->left);

        arr[i++] = tr;

        treetoarray(arr, tr->right);
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


/* wordprint: print the words in array "arr" and their counting. */

void wordprint(struct tnode **arr, int size)
{
    int i;

    for(i = 0; i < size; i++)
        printf("%5d   %s\n", arr[i]->count, arr[i]->word);
}
