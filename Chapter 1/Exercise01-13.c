/* Exercise 1-13. Write a program to print a histogram of the lengths of words
   in its input. It is easy to draw the histogram with the bars horizontal; a
   vertical orientation is more challenging. */

#include <stdio.h>

#define MAXLEN 20   /* Max length of words accepted to count. */
#define IN 1        /* Inside a word */
#define OUT 0       /* Outside a word */

main()
{
    int c, i, j, state, wlen;
    int wcount[MAXLEN];

    for(i = 0; i < MAXLEN; ++i)
        wcount[i] = 0;

    state = OUT;

    wlen = 0;

    printf("\nEnter a text:\n\n");

    while( (c = getchar()) != EOF )
    {
        if(state == OUT && c != ' ' && c != '\n' && c != '\t')
            state = IN;

        else if( (c == ' ' || c == '\n' || c == '\t') && state == IN)
        {
            state = OUT;

            if(wlen <= MAXLEN)                      /* The histogram is of lengths up to MAXLEN. */
                ++wcount[wlen - 1];

            wlen = 0;
        }

        if(state == IN)
            ++wlen;
    }

    printf("\n\nHistogram of word lengths:\n\nlength\tcount\n\n");

    for(i = 0; i < MAXLEN; ++i)
    {
        printf("%4d\t", i + 1);

        if(wcount[i] != 0)
        {
            printf("%3d\t", wcount[i]);

            for(j = 0; j < wcount[i]; ++j)          /* Histogram bars */
                printf("* ");

            printf("\n");
        }
        else
            printf("%3d\n", wcount[i]);
    }
}
