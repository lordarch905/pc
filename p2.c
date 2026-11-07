#include <stdio.h>
#include <omp.h>

int main()
{
    int n;
    printf("Enter number of iterations: ");
    scanf("%d", &n);
    omp_set_num_threads(2);
    #pragma omp parallel for schedule(static, 2)
    for (int i = 0; i < n; i++)
    {
        int tid = omp_get_thread_num();
        if (i % 2 == 0)
        {
            int chunk_start = i;
            int chunk_end = (i + 1 < n) ? i + 1 : i;
            printf("Thread %d: Iterations %d -- %d\n", tid, chunk_start, chunk_end);
        }
    }
    return 0;
}

/*
Compile: gcc -fopenmp p2.c -o p2
Run: ./p2
Input: Enter number of iterations (e.g., 4)
*/
