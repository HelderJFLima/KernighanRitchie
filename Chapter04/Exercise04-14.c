/* Exercise 4-14. Define a macro "swap(t, x, y)" that interchanges two
   arguments of type "t". (Block structure will help.) */


#include <stdio.h>

#define swap(t, x, y)   t var; \
                        var = x; \
                        x = y; \
                        y = var;


main()
{
    int a, b;

    a = 5;

    b = 17;

    printf("\na = %d\n\nb = %d\n", a, b);

    swap(int, a, b)                                 /** macro test **/

    printf("\nswaping...\n");

    printf("\na = %d\n\nb = %d\n", a, b);

    return 0;
}
