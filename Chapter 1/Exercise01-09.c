/* Exercise 1-9. Write a program to copy its input to its output,
   replacing each string of one or more blanks by a single blank. */

#include <stdio.h>

#define FIRSTCHAR 'a'

main()
{
    int c, previous;

    printf("\nEnter a text:\n\n");

    previous = FIRSTCHAR;

    while( (c = getchar()) != EOF )
    {
        if(c == ' ')
        {
            if(previous != ' ')
                putchar(c);
        }

        if(c != ' ')
            putchar(c);

        previous = c;
    }
}
