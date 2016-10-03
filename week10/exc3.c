#include <stdio.h>
#include <stddef.h>
#include "mpi.h"

#define ROOT 0

typedef struct pckg {
        int int_val;
        double dbl_val;
} package;

int main(int argc, char* argv[]) {

    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /* create a type for struct car */
    const int nitems = 2;
    int          blocklengths[2] = {1,1};
    MPI_Datatype types[2] = {MPI_INT, MPI_DOUBLE};
    MPI_Datatype mpi_package_type;
    MPI_Aint     offsets[2];

    // Alternatively use this:
    offsets[0] = offsetof(package, int_val);
    offsets[1] = offsetof(package, dbl_val);

    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_package_type);
    MPI_Type_commit(&mpi_package_type);

    package numbers_to_send;

    while(1){
      if(rank == ROOT){
        // get input value
        scanf("%d %lf", &(numbers_to_send.int_val), &(numbers_to_send.dbl_val));
        fflush(stdin);
      }

      // MPI_Bcast(start, count, datatype, root, comm)
      MPI_Bcast(&numbers_to_send, 1, mpi_package_type, ROOT, MPI_COMM_WORLD);
      if(numbers_to_send.int_val < 0)
        break;

      printf("Hello world form process %d - received value = %d and %lf\n", rank, numbers_to_send.int_val, numbers_to_send.dbl_val);
      fflush(stdout);
    }

    MPI_Type_free(&mpi_package_type);
    MPI_Finalize();

    return 0;
}
