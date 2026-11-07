#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int rank, size, x = 100, y;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 2)
    {
        if (rank == 0)
            printf("This demo requires exactly 2 MPI processes.\n");
        MPI_Finalize();
        return 0;
    }
    if (rank == 0)
    {
        printf("Process 0 sending to Process 1...\n");
        MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 waiting to receive from Process 1...\n");
        MPI_Recv(&y, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else if (rank == 1)
    {
        printf("Process 1 sending to Process 0...\n");
        MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Process 1 waiting to receive from Process 0...\n");
        MPI_Recv(&y, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    printf("Process %d completed communication.\n", rank);
    MPI_Finalize();
    return 0;
}

/*
Compile: mpicc p6.c -o p6
Run: mpiexec -np 2 ./p6
Input: None
*/
