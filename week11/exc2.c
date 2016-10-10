#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){
  int rank, size, source, dest;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(size < 2){
    printf("error: size must be > 1\n");
    printf("example of usage: mpirun -np 2 ./exc2\n");
    MPI_Finalize();
    return 1;
  }

  // http://www.bu.edu/tech/support/research/training-consulting/online-tutorials/mpi/virtual_topology/mpi_cart_create/
  // int MPI_Cart_create(MPI_Comm comm_old, int ndims, int *dims, int *periods, int reorder, MPI_Comm *comm_cart);
  int ndims = 2; // 2-D array
  int dims[2], periods[2];

  dims[0] = 1; // numrows = 1
  dims[1] = size; // numcols = size
  periods[0] = 0; // no wraparound on rows
  periods[1] = 1; // wraparound on cols
  MPI_Comm new_comm;
  MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, 1, &new_comm);

  int coord[2];
  MPI_Cart_coords(new_comm, rank, 2, coord);
  // DEBUG
  // printf("process #%d - coord: (%d, %d)\n", rank, coord[0], coord[1]);

  // http://www.bu.edu/tech/support/research/training-consulting/online-tutorials/mpi/virtual_topology/mpi_cart_shift/
  // int MPI_Cart_shift(MPI_Comm comm, int direction, int disp, int *rank_source, int *rank_dest)
  // the direction is on column, thus direction = 1
  // displacement is 1
  MPI_Cart_shift(new_comm, 1, 1, &source, &dest);

  int input_val;
  // the first process in the array
  if(coord[1] == 0){
    printf("enter int: "); fflush(stdout);
    scanf("%d", &input_val);
    MPI_Send(&input_val, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
    printf("PROCESS #%d | source: %d -- destination: %d\n", rank, source, dest);
  }
  else{
    MPI_Recv(&input_val, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("PROCESS #%d | source: %d -- destination: %d\n", rank, source, dest);
    printf("PROCESS #%d | received: %d\n\n", rank, input_val);
    fflush(stdout);
    // size-1 is important to avoid invalid rank
    if(coord[1] < size-1){
      MPI_Send(&input_val, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
    }
  }

  MPI_Finalize();
  return 0;
}
