#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int rank, size;
    const int elements_per_proc = 2;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int total_elements = elements_per_proc * size;
    int *data = NULL;
    if (rank == 0)
    {
        data = (int*)malloc(sizeof(int) * total_elements);
        for (int i = 0; i < total_elements; i++)
        {
            data[i] = i + 1;
        }
        printf("Root process has data to scatter:\n");
        for (int i = 0; i < total_elements; i++)
        {
            printf("%d ", data[i]);
        }
        printf("\n");
    }
    int *sub_data = (int*)malloc(sizeof(int) * elements_per_proc);
    MPI_Scatter(data, elements_per_proc, MPI_INT, sub_data, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < elements_per_proc; i++)
    {
        sub_data[i] *= 2;
    }
    MPI_Gather(sub_data, elements_per_proc, MPI_INT, data, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("\nRoot process received modified data from all processes:\n");
        for (int i = 0; i < total_elements; i++)
        {
            printf("%d ", data[i]);
        }
        printf("\n");
        free(data);
    }
    free(sub_data);
    MPI_Finalize();
    return 0;
}

/*
Compile: mpicc p8.c -o p8
Run: mpirun -np 4 ./p8
Input: None
*/
