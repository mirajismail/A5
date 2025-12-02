#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[] )
{
    int rank, value, size;
    MPI_Status status;

    //Add call to mpi init
    MPI_Init(&argc, &argv);
    //Add call to get rank
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //Add call to get size of communicator
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Replace the commented lines with MPI calls
    if (rank == 0) {
        value = 5;
        printf( "Process %d sending %d\n", rank, value );
        //Insert MPI command to send value to the next rank
        MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else {
        //Insert MPI command to receive value from the previous rank
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        printf( "Process %d got %d\n", rank, value );
    if (rank < size - 1)
        //Insert MPI command to send value to the next rank
        MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize( );
    return 0;
}
