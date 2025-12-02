#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[] )
{
    int rank, value, size;
    MPI_Status status;
    MPI_Request req;

    //Add call to mpi init
    MPI_Init(&argc, &argv);
    //Add call to get rank
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //Add call to get size of communicator
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Replace the commented lines with MPI calls
    if (rank == 0) {
        value = 0;
        printf( "Process %d sending %d\n", rank, value );
        MPI_Isend(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &req);
        MPI_Wait(&req, MPI_STATUS_IGNORE);    
    } else {
        MPI_Irecv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &req);
        MPI_Wait(&req, &status);

        value += 1;
        printf("Process %d received %d\n", rank, value);

        if (rank < size - 1) {
            MPI_Isend(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &req);
            MPI_Wait(&req, MPI_STATUS_IGNORE);
        }
    }

    MPI_Finalize( );
    return 0;
}
