/* Exercise 1-4. Write a program to print the corresponding Celsius to Fahrenheit
   table. */


#include <stdio.h>


/* Print Celsius-Fahrenheit table for celsius = 0, 20, ..., 300. */

main()
{
    float celsius, fahr;
    float lower, upper, step;

    lower = 0;                  /* lower limit of temperature scale */

    upper = 300;                /* upper limit */

    step = 20;                  /* step size */

    celsius = lower;

    printf("\n     Temperatures\n\nCelsius\t\tFahrenheit\n\n");

    while(celsius <= upper)
    {
        fahr = (9.0 / 5.0) * celsius + 32.0;

        printf("%5.0f\t\t%6.0f\n", celsius, fahr);

        celsius = celsius + step;
    }
}
