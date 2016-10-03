// Reference: http://mpi.deino.net/mpi_functions/MPI_Pack.html
// and http://mpi.deino.net/mpi_functions/MPI_Unpack.html
// https://wiki.calculquebec.ca/w/MPI_Pack/en

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "mpi.h"

#define ROOT 0
#define BUFFSIZE 100

int main(int argc, char* argv[]) {

    int size, rank, int_val;
    double dbl_val;
    char pack_buff[BUFFSIZE];
    int position = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    while(1){
      if(rank == ROOT){
        // get input value
        scanf("%d %lf", &(int_val), &(dbl_val));
        fflush(stdin);

        // Reset position
        position = 0;

        MPI_Pack(&int_val, 1, MPI_INT, pack_buff, BUFFSIZE, &position, MPI_COMM_WORLD);
        MPI_Pack(&dbl_val, 1, MPI_DOUBLE, pack_buff, BUFFSIZE, &position, MPI_COMM_WORLD);
      }
      // MPI_Bcast(start, count, datatype, root, comm)
      MPI_Bcast(pack_buff, BUFFSIZE, MPI_PACKED, ROOT, MPI_COMM_WORLD);

      // This position reset is important!
      position = 0;

      MPI_Unpack(pack_buff, BUFFSIZE, &position, &int_val, 1, MPI_INT, MPI_COMM_WORLD);
      MPI_Unpack(pack_buff, BUFFSIZE, &position, &dbl_val, 1, MPI_DOUBLE, MPI_COMM_WORLD);

      if(int_val < 0)
        break;

      printf("Hello world form process %d - received value = %d and %lf\n", rank, int_val, dbl_val);
      fflush(stdout);

      // Empty pack buffer
      memset(pack_buff, 0, sizeof(pack_buff));
    }

    MPI_Finalize();

    return 0;
}
