#include <stdio.h>
#include <mpi.h>
int main (int argc, char *argv[])
{
  const int N=300;
  int i,target;
  int b[N];
  FILE *infile,*outfile;
  int rank, size;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  /* File b.data has the target value on the first line
     The remaining 300 lines of b.data have the values for the b array */ 

  // compute the range per rank
  int chunk = N / size;
  int local_b[chunk];

  if (rank == 0) {
      infile = fopen("b.data", "r");
      fscanf(infile, "%d", &target);
      for (i = 0; i < N; i++) fscanf(infile, "%d", &b[i]);
      fclose(infile);
  }

  // broadcast target
  MPI_Bcast(&target, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // scatter b into local_b
  MPI_Scatter(
      b,          // sendbuf
      chunk,
      MPI_INT,
      local_b,    // recvbuf
      chunk,
      MPI_INT,
      0,
      MPI_COMM_WORLD
  );

  char outfilename[64];
  sprintf(outfilename, "found.data_%d", rank);
  outfile = fopen(outfilename,"w") ;

  /* Search the b array and output the target locations */

  for(i=0;i<chunk;i++) {
    if(local_b[i] == target) {
      fprintf(outfile,"%d\n",rank * chunk + i + 1);
    }
  }
  fclose(outfile);

  MPI_Finalize();
 
  return 0;
}
