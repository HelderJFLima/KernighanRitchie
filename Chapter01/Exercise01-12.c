/* Exercise 1-12. Write a program that prints its input one word per line. */


#include <stdio.h>


main()
{
    int c;

    printf("\nEnter a text:\n\n");

    while( (c = getchar()) != EOF )
    {
        if(c == ' ' || c == '\t')
            putchar('\n');
        else
            putchar(c);
    }
}
