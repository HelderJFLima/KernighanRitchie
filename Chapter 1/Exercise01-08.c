/* Exercise 1-8. Write a program to count blanks, tabs, and newlines. */

#include <stdio.h>

main()
{
    int c, nb, nt, nnl;

    nb = 0;

    nt = 0;

    nnl = 0;

    printf("\nEnter a text:\n\n");

    while( (c = getchar()) != EOF )
    {
        if(c == ' ')
            ++nb;

        if(c == '\t')
            ++nt;

        if(c == '\n')
            ++nnl;
    }

    printf("\n\nBlanks counting:\n");

    printf("\nBlanks: %d\n\nTabs: %d\n\nNew lines: %d\n\nTotal: %d\n\n", nb, nt, nnl, nb + nt + nnl);
}
