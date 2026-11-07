#include <stdio.h>
#include <omp.h>
#include <time.h>

int is_prime(int n)
{
    if (n < 2)
        return 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    long n = 10000000;
    clock_t start, end;
    double cpu_time;
    printf("\nThe range of numbers is 1 to %ld\n", n);
    printf("------------------------------------------\n");
    start = clock();
    for (long i = 1; i <= n; i++)
    {
        is_prime(i);
    }
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time to compute prime numbers (Serial): %f seconds\n", cpu_time);
    start = clock();
    #pragma omp parallel for schedule(dynamic)
    for (long i = 1; i <= n; i++)
    {
        is_prime(i);
    }
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time to compute prime numbers (Parallel): %f seconds\n", cpu_time);
    return 0;
}

/*
Compile: gcc -fopenmp p4.c -o p4
Run: ./p4
Input: None
*/
