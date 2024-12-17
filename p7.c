#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size, root = 0;
    int data_to_bcast, local_value, global_sum;
    int *send_data = NULL, *gathered_data = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Step 1: Broadcast a value from the root process
    if (rank == root) {
        data_to_bcast = 10;
        printf("Root process broadcasting value: %d\n", data_to_bcast);
    }
    MPI_Bcast(&data_to_bcast, 1, MPI_INT, root, MPI_COMM_WORLD);

    // Step 2: Scatter an array of values from the root process
    if (rank == root) {
        send_data = (int*)malloc(size * sizeof(int));
        for (int i = 0; i < size; i++) send_data[i] = (i + 1) * 2; // Example values
    }
    MPI_Scatter(send_data, 1, MPI_INT, &local_value, 1, MPI_INT, root, MPI_COMM_WORLD);
    printf("Process %d received value: %d\n", rank, local_value);

    // Step 3: Each process performs computation (multiply local value with the broadcast value)
    local_value *= data_to_bcast;

    // Step 4: Gather results back to the root process
    if (rank == root) {
        gathered_data = (int*)malloc(size * sizeof(int));
    }
    MPI_Gather(&local_value, 1, MPI_INT, gathered_data, 1, MPI_INT, root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("Gathered results at root process: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", gathered_data[i]);
        }
        printf("\n");
    }

    // Step 5: Reduce the gathered results to compute the global sum
    MPI_Reduce(&local_value, &global_sum, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("Global sum of results: %d\n", global_sum);
    }

    if (send_data) free(send_data);
    if (gathered_data) free(gathered_data);

    MPI_Finalize();
    return 0;
}
