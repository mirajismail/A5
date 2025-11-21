#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[])
{
    // myrank - current process's id within MPI_COMM_WORLD
    // size - number of processes in MPI_COMM_WORLD
    int myrank, size;

    // initialize Mpi
    MPI_Init(&argc, &argv);

    // Query MPI for this process's rank
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    // How many processes live in MPI_COMM_WORLD
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Processor %d of %d: Hello World!\n", myrank, size);

    // Close Mpi env
    MPI_Finalize();

    return 0;
}
