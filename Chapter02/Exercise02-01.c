/* Exercise 2-1. Write a program to determine the ranges of char, short, int,
   and long variables, both signed and unsigned, by printing appropriate values
   from standard headers and by direct computation. Harder if you compute them:
   determine the ranges of the various floating-point types. */


#include <stdio.h>
#include <float.h>
#include <limits.h>


main()
{
    printf("\nRanges of different types:\n\n");

    printf("\nsigned char:\t   %d to %d\n", SCHAR_MIN, SCHAR_MAX);

    printf("\nunsigned char:\t   0 to %d\n", UCHAR_MAX);

    printf("\nsigned short:\t   %d to %d\n", SHRT_MIN, SHRT_MAX);

    printf("\nunsigned short:\t   0 to %d\n", USHRT_MAX);

    printf("\nsigned int:\t   %d to %d\n", INT_MIN, INT_MAX);

    printf("\nunsigned int:\t   0 to %u\n", UINT_MAX);  /* The printf argument
                                                           "%u" was found in
                                                           Appendix B.1.2. */

    printf("\nsigned long:\t   %d to %ld\n", LONG_MIN, LONG_MAX);

    printf("\nunsigned long:\t   0 to %u\n", ULONG_MAX);

    printf("\nfloat:\t\t   %e to %e\n", FLT_MIN, FLT_MAX);

    printf("\ndouble:\t\t   %e to %e\n", DBL_MIN, DBL_MAX);

    printf("\nlong double:\t   %e to %e\n\n", LDBL_MIN, LDBL_MAX);

    return 0;
}
