/* Exercise 3-1. Our binary search makes two tests inside the loop, when one
   would suffice (at the price of more tests outside.) Write a version with only
   one test inside the loop and measure the difference in run-time. */


/* The book did not teach to measure run-time until now. I used the measure
   that my IDE gives in its terminal. The 1st version of binsearch consumed
   0.016 seconds and the 2nd version consumed 0.015 seconds. That doesn't
   seem like a significant difference... */


#include <stdio.h>

#define SIZE 500000                         /* Array size */

int binsearch1(int x, int arr[], int size);

int binsearch2(int x, int arr[], int size);


main()
{
    int i, pos;
    int arr[SIZE], x[10];

    x[0] = 996245;
    x[1] = 506475;
    x[2] = 814227;
    x[3] = 454135;
    x[4] = 593157;
    x[5] = 950958;
    x[6] = 700822;
    x[7] = 382786;
    x[8] = 616832;
    x[9] = 74308;

    arr[0] = 1;

    for(i = 1; i < SIZE; i++)
        arr[i] = arr[i - 1] + 2;  /* Odd numbers */

    printf("\nThis program does a binary search of the following ");

    printf("numbers in an array\nof odd integers from 1 to 999999 ");

    printf("and returns their positions.\n\n");

/*    for(i = 0; i < 10; i++)
    {
        pos = binsearch1(x[i], arr, SIZE);              /** binsearch1 test **/

/*        if(pos >= 0)
            printf("number %6d\tposition: %d\n", x[i], pos);
        else
            printf("number %6d\tposition: NOT FOUND\n", x[i] );
    }*/

    for(i = 0; i < 10; i++)
    {
        pos = binsearch2(x[i], arr, SIZE);              /** binsearch2 test **/

        if(pos >= 0)
            printf("number %6d\tposition: %d\n", x[i], pos);
        else
            printf("number %6d\tposition: NOT FOUND\n", x[i] );
    }

    return 0;
}


/* binsearch1: find "x" in a[0] <= a[1] <= ... <= a[n-1]. Return the position
               or -1 if "x" is not found. */

int binsearch1(int x, int a[], int n)
{
    int high, low, mid;

    low = 0;

    high = n - 1;

    while(low <= high)
    {
        mid = (low + high) / 2;

        if(x < a[mid])
            high = mid - 1;

        else if(x > a[mid])
            low = mid + 1;

        else                                /* Found match */
            return mid;
    }

    return -1;                              /* No match */
}


/* binsearch2: find "x" in a[0] <= a[1] <= ... <= a[n-1]. Return the position
               or -1 if "x" is not found. Only-one-test-inside-the-loop
               version. */

int binsearch2(int x, int a[], int n)
{
    int high, low, mid;

    low = 0;

    high = n - 1;

    while(low <= high)
    {
        mid = (low + high) / 2;

        if(x >= a[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }

    if(x == a[low])                         /* Found match */
        return low;

    else if(x == a[high])
        return high;

    else
        return -1;                          /* No match */
}
