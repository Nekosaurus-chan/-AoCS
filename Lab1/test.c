#include <stdio.h>
#include <math.h>

float Y(float x) 
{
    return sin(x);
}

int factorial(int n) 
{
    int result = 1;

    for (int i = 1; i <= n; i++) 
    {
        result *= i;
    }

    return result;
}

float S(float x, int n)
{
    float result = 0;

    for (int i = 0; i <= n; i++) 
    {
        result += pow(-1, i) * pow(x, 2 * i + 1) / factorial(2 * i + 1);
    }

    return result;
}