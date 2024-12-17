//total number of mangoes picked by n robots
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    int rank, size, mangoes, total_mangoes;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank);
    mangoes = rand() % 100 + 1;
    printf("Robot %d picked %d mangoes.\n", rank, mangoes);

    MPI_Reduce(&mangoes, &total_mangoes, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total mangoes picked by %d robots: %d\n", size, total_mangoes);
    }

    MPI_Finalize();
    return 0;
}
