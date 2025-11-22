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
  infile = fopen("b.data","r" ) ;
      
  /* read in target */
  fscanf(infile,"%d", &target);

  /* read in b array */
  for(i=0;i<N;i++) {
    fscanf(infile,"%d", &b[i]);
  }
  fclose(infile);

  // compute the range per rank
  int chunk = N / size;
  int start = rank * chunk;
  int end = (rank == size - 1) ? N : start + chunk;


  // open output file per rank
  char outfilename[64];
  sprintf(outfilename, "found.data_%d", rank);
  outfile = fopen(outfilename,"w") ;

  /* Search the b array and output the target locations */

  for(i=start;i<end;i++) {
    if( b[i] == target) {
      fprintf(outfile,"%d\n",i+1);
    }
  }
  fclose(outfile);

  MPI_Finalize();
 
  return 0;
}
