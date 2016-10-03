#include <stdio.h>
#include "mpi.h"

#define ROOT 0

int main(int argc, char* argv[]){
  int rank, size, input_val;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  while(1){
    if(rank == ROOT){
      // get input value
      scanf("%d", &input_val);
      fflush(stdin);
    }
    // MPI_Bcast(start, count, datatype, root, comm)
    MPI_Bcast(&input_val, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
    if(input_val < 0)
      break;

    printf("Hello world form process %d - received value = %d\n", rank, input_val);
    fflush(stdout);
  }
  MPI_Finalize();
  return 0;
}
