#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

extern float Y(float x);
extern int factorial(int n);
extern float S(float x, int n);

int main() 
{
    float a, b, h, epsilon, y, s;
    int n = 0;

    printf("Enter a, b, h, epsilon: ");
    scanf("%f %f %f %f", &a, &b, &h, &epsilon);

    for (float x = a; x <= b; x += h)
    {
        clock_t start = clock();

        if(2 * n + 1 <= 13)
        {

            if(epsilon >= abs(Y(x) - S(x, n)))
            {
                n++;
            }

            else
            {
                break;
            }
        }

        else
        {
            break;
        }

        clock_t end = clock();
        double time = (double)(end - start) / CLOCKS_PER_SEC;

        printf("x = %f, Y = %f, S = %f, n = %d, time = %f, fact = %d\n", x, Y(x), S(x, n), n, time, factorial(2 * n + 1));
    }

    return 0;
}