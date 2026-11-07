#include <stdio.h>
#include <omp.h>
#include <time.h>

int ser_fb(long int n)
{
    if (n < 2)
        return n;
    long int x, y;
    x = ser_fb(n - 1);
    y = ser_fb(n - 2);
    return x + y;
}

int fib(long int n)
{
    if (n < 2)
        return n;
    long int x, y;
    #pragma omp task shared(x)
    x = fib(n - 1);
    #pragma omp task shared(y)
    y = fib(n - 2);
    #pragma omp taskwait
    return x + y;
}

int main()
{
    long int n, result;
    clock_t start, end;
    double cpu_time;
    printf("\nEnter the value of n: ");
    scanf("%ld", &n);
    start = clock();
    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Fibonacci(%ld) = %ld\n", n, result);
    printf("\nThe time used to execute the program in parallel mode = %f", cpu_time);
    start = clock();
    result = ser_fb(n);
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nFibonacci(%ld) = %ld\n", n, result);
    printf("\nThe time used to execute the program in sequential mode = %f\n", cpu_time);
    return 0;
}

/*
Compile: gcc -fopenmp p3.c -o p3
Run: ./p3
Input: Enter the value of n (e.g., 20)
*/
