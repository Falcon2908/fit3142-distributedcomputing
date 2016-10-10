#include <stdio.h>
#include <mpi.h>

#define ROOT 0

int main(int argc, char* argv[]){
  int rank, size;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(size < 2){
    perror("size must be 2 or more");
    return 1;
  }

  int input_val;
  if(rank == ROOT){
    scanf("%d", &input_val);
    MPI_Send(&input_val, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  }
  else{
    MPI_Recv(&input_val, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("process %d - received: %d\n", rank, input_val);

    // size-1 is important to avoid invalid rank
    if(rank < size-1){
      MPI_Send(&input_val, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
    }
  }

  MPI_Finalize();
  return 0;
}
