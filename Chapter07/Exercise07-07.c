/* Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its
                 input from a set of named files or, if no files are named as
                 arguments, from the standard input. Should the file name be
                 printed when a matching line is found?


/* Yes; the file name will be printed when a matching line is found. */


#include <stdio.h>
#include <stdlib.h>         /* For free and malloc */
#include <string.h>         /* For strcpy, strlen and strstr */

#define MAXLINE  1000       /* Maximum input line length */
#define MAXFNAME 200        /* Maximum file name length */
#define MAXPTRN  100        /* Maximum pattern length */


struct flistnode
*checkfile(char *f, char *p, struct flistnode *ln);

void flistprint(struct flistnode *p);

void freeflist(struct flistnode *p);

void rmvnewline(char *s);


/* Node for list with lines that match the pattern */

struct llistnode { int linenum;
                   char *line;
                   struct llistnode *next; };


/* Node for list with files that have lines matching pattern */

struct flistnode { char *filename;
                   struct llistnode *llist;
                   struct llistnode *lastnode;
                   struct flistnode *next;    };


/** find: print lines that match pattern from 1st arg; also print the names of
          the files that match the search. */

main(int argc, char *argv[])
{
    char *pattern;
    struct flistnode *flist = NULL;     /* Pointer to the list of files */
    struct flistnode *lnp = NULL;       /* Pointer to the last added list node */
    struct flistnode *p;                /* Auxiliary pointer */

    if(argc > 2)                        /** File names as arguments */
    {
        pattern = *++argv;              /* The first argument is the pattern. */

        while(*++argv)                  /* Check all files. */
        {
            p = checkfile(*argv, pattern, lnp);

            if(p != NULL && lnp != NULL)

                lnp = p;

            else if(p != NULL)          /* Add first node */
                flist = lnp = p;
        }
    }
    else if(argc == 2)                  /** No file names as arguments */
    {
        char fname[MAXFNAME];

        printf("\nEnter the name of the file you ");

        printf("want to search for the pattern: ");

        if( fgets(fname, MAXFNAME, stdin) != NULL )
        {
            pattern = *++argv;

            rmvnewline(fname);          /* Remove new line. */

            p = checkfile(fname, pattern, lnp);

            if(p != NULL)
                flist = p;
        }
        else
        {
            printf("\n\n* ERROR *: error reading file name\n\n");

            return 1;
        }
    }
    else                                /** No arguments */
    {
        char fname[MAXFNAME], ptrn[MAXPTRN];

        printf("\nEnter the pattern you want to search for: ");

        if( fgets(ptrn, MAXPTRN, stdin) != NULL )
        {
            printf("\nEnter the name of the file you ");

            printf("want to search for the pattern: ");

            if( fgets(fname, MAXFNAME, stdin) != NULL )
            {
                rmvnewline(ptrn);       /* Remove new line. */

                rmvnewline(fname);

                p = checkfile(fname, ptrn, lnp);

                if(p != NULL)
                    flist = p;
            }
            else
            {
                printf("\n\n* ERROR *: error reading file name\n\n");

                return 1;
            }
        }
        else
        {
            printf("\n\n* ERROR *: error reading pattern\n\n");

            return 2;
        }
    }

    if(flist != NULL)                   /* Print results. */
    {
        printf("\n\nMatches found:\n\n");

        flistprint(flist);

        printf("\n");
    }
    else
        printf("\n\nNo matches found.\n\n");

    freeflist(flist);                   /* Free up memory space. */

    return 0;
}


/* addflist: add a flistnode at "p" or at the next node. */

struct flistnode
*addflist(struct flistnode *p, char *fstr)
{
    struct flistnode *flalloc(void);
    char *strdupl(char *);

    if(p == NULL)                               /* New node */
    {
        p = flalloc();

        if(p != NULL)
        {
            if( ( p->filename = strdupl(fstr) ) == NULL )   /* Copy file name. */
            {
                printf("\n* strdupl ERROR *: malloc ");

                printf("returned NULL for file: %s\n\n", fstr);
            }

            p->llist = p->lastnode = NULL;

            p->next = NULL;
        }
        else
        {
            printf("\n* llalloc ERROR *: malloc ");

            printf("returned NULL for file: %s\n\n", fstr);
        }

        return p;
    }
    else                                        /* There is already a node */
    {
        p->next = addflist(p->next, fstr);

        return p->next;                         /* New last node */
    }
}


/* addllist: add a llistnode at "p" or at the next node. */

struct llistnode
*addllist(struct llistnode *p, int num, char *str)
{
    struct llistnode *llalloc(void);
    char *strdupl(char *);

    if(p == NULL)                               /* New node */
    {
        p = llalloc();

        if(p != NULL)
        {
            p->linenum = num;

            if( ( p->line = strdupl(str) ) == NULL )    /* Copy string. */
            {
                printf("\n* strdupl ERROR *: malloc returned NULL ");

                printf("for:\n\nLine %d: %s\n\n", num, str);
            }

            p->next = NULL;
        }
        else
        {
            printf("\n* llalloc ERROR *: malloc returned NULL ");

            printf("for:\n\nLine %d: %s\n\n", num, str);
        }

        return p;
    }
    else                                        /* There is already a node */
    {
        p->next = addllist(p->next, num, str);

        return p->next;                         /* New last node */
    }
}


/* checkfile: open file to search for pattern "ptrn"; return a pointer to a new
              file node or NULL if none were created. */

struct flistnode
*checkfile(char *file, char *ptrn, struct flistnode *lastn)
{
    struct flistnode
    *searchfile(FILE *, char *, char *, struct flistnode *);

    FILE *f;
    struct flistnode *fp = NULL;

    f = fopen(file, "r");

    if(f != NULL)

        fp = searchfile(f, ptrn, file, lastn);  /* Search for the pattern. */

    else
        printf("\n* checkfile ERROR *: error opening file '%s'\n\n", file);

    fclose(f);

    return fp;
}


/* flalloc: make a flistnode. */

struct flistnode
*flalloc(void)
{
    return (struct flistnode *)malloc( sizeof(struct flistnode) );
}


/* flistprint: print the list of files "p". */

void flistprint(struct flistnode *p)
{
    void llistprint(struct llistnode *);

    if(p != NULL)
    {
        printf("\nFile: '%s'\n\n", p->filename);

        llistprint(p->llist);

        flistprint(p->next);
    }
}


/* freeflist: deallocate space used by a list of files. */

void freeflist(struct flistnode *p)
{
    void freellist(struct llistnode *);

    if(p != NULL)
    {
        if(p->next != NULL)
            freeflist(p->next);

        free(p->filename);

        freellist(p->llist);

        free(p);
    }
}


/* freellist: deallocate space used by a list of lines. */

void freellist(struct llistnode *p)
{
    if(p != NULL)
    {
        if(p->next != NULL)
            freellist(p->next);

        free(p->line);

        free(p);
    }
}


/* llalloc: make a llistnode. */

struct llistnode
*llalloc(void)
{
    return (struct llistnode *)malloc( sizeof(struct llistnode) );
}


/* llistprint: print the list of lines "p". */

void llistprint(struct llistnode *p)
{
    if(p != NULL)
    {
        printf("  Line %4d: %s\n", p->linenum, p->line);

        llistprint(p->next);
    }
}


/* rmvnewline: remove new line character from end of string if exists. */

void rmvnewline(char *s)
{
    s = s + strlen(s);

    if(*--s == '\n')
        *s = '\0';
}


/* searchfile: locate pattern "ptrn" in file "f"; if found, create a new file
               node and a list of occurrences of lines; return the pointer to
               the new file node or NULL if none were created. */

struct flistnode
*searchfile(FILE *f, char *ptrn, char *fname, struct flistnode *lastn)
{
    struct flistnode *addflist(struct flistnode *, char *);
    struct llistnode *addllist(struct llistnode *, int, char *);

    int lnum = 0;                   /* Line number */
    char line[MAXLINE];
    char *lread;                    /* To check reading errors */
    struct llistnode *lp;
    struct flistnode *fp = NULL;

    while( !feof(f) )
    {
        lread = fgets(line, MAXLINE, f);                    /** Get line. */

        lnum++;

        if(lread != NULL && strstr(line, ptrn) != NULL)     /** Search. */
        {
            if(fp != NULL)                          /* The node already exists. */
            {
                lp = addllist(fp->lastnode, lnum, line);    /* New line node. */

                if(lp != NULL && fp->llist != NULL)

                    fp->lastnode = lp;

                else if(lp != NULL)                 /* If there's no list yet */
                    fp->llist = fp->lastnode = lp;
            }
            else                                    /* A new node is required. */
            {
                fp = addflist(lastn, fname);        /* New file node. */

                if(fp != NULL)
                {
                    fp->lastnode = addllist(fp->lastnode, lnum, line);

                    fp->llist = fp->lastnode;
                }
            }
        }
        else if( ferror(f) )
        {
            printf("\n* searchfile ERROR *: error reading ");

            printf("file '%s' on line %d\n\n", fname, lnum);

            break;
        }
    }

    return fp;
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
