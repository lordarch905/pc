#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int value;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    value = rank + 1;
    int sum_result, prod_result, max_result, min_result;
    int all_sum, all_prod, all_max, all_min;
    MPI_Reduce(&value, &sum_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &prod_result, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &max_result, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &min_result, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("=== MPI_Reduce results at root process ===\n");
        printf("Sum: %d\n", sum_result);
        printf("Prod: %d\n", prod_result);
        printf("Max: %d\n", max_result);
        printf("Min: %d\n", min_result);
    }
    MPI_Allreduce(&value, &all_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &all_prod, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &all_max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &all_min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    printf("Process %d:\n", rank);
    printf("  Allreduce Sum = %d\n", all_sum);
    printf("  Allreduce Prod = %d\n", all_prod);
    printf("  Allreduce Max = %d\n", all_max);
    printf("  Allreduce Min = %d\n", all_min);
    MPI_Finalize();
    return 0;
}

/*
Compile: mpicc p9.c -o p9
Run: mpirun -np 4 ./p9
Input: None
*/
