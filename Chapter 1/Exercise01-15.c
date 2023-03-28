/* Exercise 1-15. Rewrite the temperature conversion program of Section 1.2
   to use a function for conversion. */

#include <stdio.h>

/* The Exercise 1-3 was chosen to do this. */

/* print Fahrenheit-Celsius table for fahr = 0, 20, ..., 300; */
/* using-a-function version */

float FahrenheitToCelsius(float fahr);

main()
{
    float fahr, lower, upper, step;

    lower = 0;                      /* lower limit of temperature scale */

    upper = 300;                    /* upper limit */

    step = 20;                      /* step size */

    fahr = lower;

    printf("\n     Temperatures\n\nFahrenheit\tCelsius\n\n");

    while(fahr <= upper)
    {
        printf("%6.0f\t\t%6.1f\n", fahr, FahrenheitToCelsius(fahr) );

        fahr = fahr + step;
    }

    return 0;
}

float FahrenheitToCelsius(float fahrenheit)
{
    return (5.0 / 9.0) * (fahrenheit - 32.0);
}
