/* Exercise 1-14. Write a program to print a histogram of the frequencies
   of different characters in its input. */

#include <stdio.h>

#define NUMCHAR 26      /* Number of characters in the alphabet */

main()
{
    int c, i, j;
    int ccount[NUMCHAR];

    for(i = 0; i < NUMCHAR; ++i)
        ccount[i] = 0;

    printf("\nEnter a text:\n\n");

    while( (c = getchar()) != EOF )                 /* Counts characters */
    {
        if(c >= 'a' && c <= 'z')
            ++ccount[c - 'a'];

        else if(c >= 'A' && c <= 'Z')
            ++ccount[c - 'A'];
    }

    printf("\n\nFrequencies of characters:\n\ncharacter   count\n\n");

    for(i = 0; i < NUMCHAR; ++i)
    {
        printf("    %c        ", 'a' + i);

        if(ccount[i] != 0)
        {
            printf("%3d    ", ccount[i]);

            for(j = 0; j < ccount[i]; ++j)          /* Histogram bars */
                printf("*");

            printf("\n");
        }
        else
            printf("%3d\n", ccount[i]);
    }
}
