/* Exercise 1-10. Write a program to copy its input to its output, replacing
   each tab by \t, each backspace by \b, and each backslash by \\. This makes
   tabs and backspaces visible in an unambiguous way. */


#include <stdio.h>


main()
{
    int c;

    printf("\nEnter a text:\n\n");

    while( (c = getchar()) != EOF )
    {
        if(c == '\t')
        {
            putchar('\\');

            putchar('t');
        }

        if(c == '\b')               /* It's normal that backspace does not */
        {                           /* appear in some consoles. */
            putchar('\\');

            putchar('b');
        }

        if(c == '\\')
        {
            putchar('\\');

            putchar('\\');
        }

        if(c != '\t')               /* If this looks strange, read the README */
        {                           /* file for explanations. */
            if(c != '\b')
            {
                if(c != '\\')
                    putchar(c);
            }
        }
    }
}
