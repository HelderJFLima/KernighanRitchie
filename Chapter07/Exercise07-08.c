/* Exercise 7-8. Write a program to print a set of files, starting each new
   one on a new page, with a title and a running page count for each file. */


#include <stdio.h>

#define MAXLINE  1000       /* Maximum input line length */
#define PGSIZE   10         /* Maximum number of lines in each page */


void printfile(char *file, int psize);


/* print a set of files, starting each new one on a new page, with a title and
   a running page count for each file. */

main(int argc, char *argv[])
{
    if(argc >= 2)
    {
        while(*++argv)
            printfile(*argv, PGSIZE);
    }
    else
    {
        printf("\n* ERROR *: no arguments\n\n");

        return 1;
    }

    return 0;
}


/* printfile: read a file and print its contents; return last page number. */

void printfile(char *file, int psize)
{
    void newpage(char *, int);

    int lcount = 0;                     /* Line count */
    int pnum = 0;                       /* Page number */
    char line[MAXLINE], *l;
    FILE *f;

    newpage(file, ++pnum);              /* Print page header. */

    f = fopen(file, "r");

    if(f != NULL)
    {
        while( !feof(f) )
        {
            l = fgets(line, MAXLINE, f);

            lcount++;

            if(l != NULL && lcount <= psize)

                printf("%s", line);

            else if(l != NULL)          /* Page overflow */
            {
                newpage(file, ++pnum);

                printf("%s", line);

                lcount = 1;
            }
            else if( ferror(f) )
            {
                printf("\n* ERROR *: error reading file");

                printf("'%s' on line %d\n\n", file, lcount);

                break;
            }
        }
    }
    else
        printf("\n* ERROR *: error opening file '%s'\n\n", file);

    fclose(f);
}


/* newpage: print the start of a new page with a title and a line number. */

void newpage(char *file, int pg)
{
    printf("\n\n\n\nFile: %s\t\t\t\t\t\t\t\t\tpage %d\n\n\n", file, pg);
}
