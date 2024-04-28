#include <iostream>
#include <cmath>
#include <thread>
#include <vector>

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

void worker(float a, float b, float h, float epsilon, int &n)
{
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

        std::cout << "x = " << x << " Y = " << Y(x) << " S = " << S(x, n) << " n = " << n << " time = " << time << " fact = " << factorial(2 * n + 1) << std::endl;
    }
}

int main() 
{
    float a, b, h, epsilon;
    int n = 0;

    std::cout << "Enter a, b, h, epsilon: ";
    scanf("%f %f %f %f", &a, &b, &h, &epsilon);

    int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(num_threads);

    float range = (b - a) / num_threads;

    for (int i = 0; i < num_threads; ++i) 
    {
        threads[i] = std::thread(worker, a + i * range, a + (i + 1) * range, h, epsilon, std::ref(n));
    }

    for (auto& th : threads) 
    {
        th.join();
    }

    return 0;
}
