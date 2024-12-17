// MPI Collective Communications
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv) {
    int rank, size, root = 0;
    int data_size = 8;  // Total number of data elements
    int *data = NULL, recv_data;
    int local_square, total_sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int elements_per_process = data_size / size;

    if (rank == root) {
        data = (int*)malloc(data_size * sizeof(int));
        printf("Data to be scattered: ");
        for (int i = 0; i < data_size; i++) {
            data[i] = i + 1;  // Initialize data as 1, 2, ..., data_size
            printf("%d ", data[i]);
        }
        printf("\n");
    }

    MPI_Scatter(data, elements_per_process, MPI_INT, &recv_data, elements_per_process, MPI_INT, root, MPI_COMM_WORLD);

    local_square = recv_data * recv_data;
    printf("Process %d received %d, squared it to %d\n", rank, recv_data, local_square);

    MPI_Reduce(&local_square, &total_sum, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("The total sum of squares is: %d\n", total_sum);
    }

    if (rank == root) {
        free(data);
    }

    MPI_Finalize();
    return 0;
}
