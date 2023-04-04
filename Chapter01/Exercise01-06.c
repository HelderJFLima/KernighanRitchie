/* Exercise 1-6. Verify that the expression getchar() != EOF is 0 or 1. */


#include <stdio.h>


main()
{
    printf("\nEnter a character: ");

    printf("\n\"getchar() != EOF\" is equal to %d\n\n", getchar() != EOF);
}
