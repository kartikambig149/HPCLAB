#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MSG_TAG 0
#define N 10

int main(int argc, char** argv) {
    int rank, size, data[N];
    MPI_Request req;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Initialize data at root process
        for (int i = 0; i < N; i++) {
            data[i] = i + 1;
        }

        printf("Process %d sending data: ", rank);
        for (int i = 0; i < N; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");

        // Blocking send to process 1
        MPI_Send(data, N, MPI_INT, 1, MSG_TAG, MPI_COMM_WORLD);

        // Non-blocking receive from process 1
        MPI_Irecv(data, N, MPI_INT, 1, MSG_TAG, MPI_COMM_WORLD, &req);

        // Wait for non-blocking receive to complete
        MPI_Wait(&req, &status);

        printf("Process %d received data: ", rank);
        for (int i = 0; i < N; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    } else if (rank == 1) {
        // Blocking receive from process 0
        MPI_Recv(data, N, MPI_INT, 0, MSG_TAG, MPI_COMM_WORLD, &status);

        printf("Process %d received data: ", rank);
        for (int i = 0; i < N; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");

        // Modify data
        for (int i = 0; i < N; i++) {
            data[i] *= 2;
        }

        // Non-blocking send to process 0
        MPI_Isend(data, N, MPI_INT, 0, MSG_TAG, MPI_COMM_WORLD, &req);

        // Wait for non-blocking send to complete
        MPI_Wait(&req, &status);
    }

    MPI_Finalize();
    return 0;
}
