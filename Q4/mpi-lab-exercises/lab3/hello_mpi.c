#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[])
{
  int myrank, size;

  MPI_File fh;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  // Open file collectively
  MPI_File_open(MPI_COMM_WORLD, "hello.txt",
                MPI_MODE_CREATE | MPI_MODE_WRONLY,
                MPI_INFO_NULL, &fh);

  // Build the message
  char buf[64];
  int len = snprintf(buf, sizeof(buf), 
          "Processor %d of %d: Hello World!\n", myrank + 1, size);

  // Each rank writes at a unique offset
  MPI_Offset offset = myrank * 64;
  MPI_File_write_at(fh, offset, buf, len, MPI_CHAR, MPI_STATUS_IGNORE);
  MPI_File_close(&fh);
  MPI_Finalize();

  return 0;
}
