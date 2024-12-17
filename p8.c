//Cartesian Virtual Topology in MPI.
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size, dims[2], periods[2] = {0, 0}, coords[2];
    MPI_Comm cart_comm;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    dims[0] = dims[1] = 0;  // Let MPI decide dimensions
    MPI_Dims_create(size, 2, dims);

    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &cart_comm);
    MPI_Cart_coords(cart_comm, rank, 2, coords);

    printf("Process %d: Coordinates = (%d, %d)\n", rank, coords[0], coords[1]);

    MPI_Comm_free(&cart_comm);
    MPI_Finalize();
    return 0;
}
