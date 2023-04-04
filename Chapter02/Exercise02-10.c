/* Exercise 2-10. Rewrite the function "lower", which converts upper case
   letters to lower case, with a conditional expression instead of "if-else". */


#include <stdio.h>

int lower(int character);


main()
{
    int c;

    printf("\nEnter letters:\n\n");

    while( (c = getchar()) != EOF )
        if(c != '\n')
            printf("\n%c -> %c\n\n\n", c, lower(c) );

    return 0;
}


/* lower: convert "c" to lower case; ASCII only; 2nd version. */

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
}
