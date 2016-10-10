#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]){
  int errs = 0;
  int size, rank;
  int source, dest;
  int dims[2], periods[2];

  MPI_Comm comm;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  dims[0] = 3; // numrows = 3
  dims[1] = 3; // numcols = 3
  periods[0] = 1; // wraparound rows
  periods[1] = 1; // wraparound columns
  MPI_Cart_create( MPI_COMM_WORLD, 2, dims, periods, 1, &comm );
  if(rank == 3){
    int i;
    for(i = 0; i < 3; i++){
      int j;
      for(j = 0; j < 5; j++){
        int rank;
        int coordinate[2] = {i, j};
        MPI_Cart_rank( comm, coordinate, &rank);
        printf("My rank is %d\n", rank);
      }
    }
    MPI_Cart_shift( comm, 1, 1, &source, &dest );
    printf("source: %d\n", source);
    printf("destination: %d\n", dest);
  }
  // printf( "Source for shift 1 is %d - rank: %d\n", source, rank );fflush(stdout);
  // printf( "Dest for shift 1 is %d - rank: %d\n", dest, rank );fflush(stdout);

  // if (source != ((rank - 1 + size) % size)) {
  //    errs++;
  //    printf( "Source for shift 1 is %d\n", source );fflush(stdout);
  // }
  // if (dest != ((rank + 1) % size)) {
  //    errs++;
  //    printf( "Dest for shift 1 is %d\n", dest );fflush(stdout);
  // }
  // MPI_Cart_shift( comm, 0, 0, &source, &dest );
  // if (source != rank) {
  //    errs++;
  //    printf( "Source for shift 0 is %d\n", source );fflush(stdout);
  // }
  // if (dest != rank) {
  //    errs++;
  //    printf( "Dest for shift 0 is %d\n", dest );fflush(stdout);
  // }
  // MPI_Cart_shift( comm, 0, -1, &source, &dest );
  // if (source != ((rank + 1) % size)) {
  //    errs++;
  //    printf( "Source for shift -1 is %d\n", source );fflush(stdout);
  // }
  // if (dest != ((rank - 1 + size) % size)) {
  //    errs++;
  //    printf( "Dest for shift -1 is %d\n", dest );fflush(stdout);
  // }

  MPI_Comm_free( &comm );
  MPI_Finalize();
  return 0;
}
