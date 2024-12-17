#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function to allocate a matrix of size N x N
double** allocate_matrix(int N) {
    double** mat = (double**)malloc(N * sizeof(double*));
    for (int i = 0; i < N; i++) {
        mat[i] = (double*)malloc(N * sizeof(double));
    }
    return mat;
}

// Function to free a matrix of size N x N
void free_matrix(double** mat, int N) {
    for (int i = 0; i < N; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Function to multiply two matrices
void multiply_matrices(double** A, double** B, double** C, int N) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char** argv) {
    int N = 3000;  // Size of the matrices (1000, 2000, or 3000 dimensions)
    double** A = allocate_matrix(N);
    double** B = allocate_matrix(N);
    double** C = allocate_matrix(N);

    // Initialize matrices A and B with some values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (i + j) % 100;  // Sample values
            B[i][j] = (i - j) % 100;  // Sample values
        }
    }

    double start_time, end_time;

    // Sequential matrix multiplication
    start_time = omp_get_wtime();
    multiply_matrices(A, B, C, N);
    end_time = omp_get_wtime();
    printf("Sequential time: %f seconds\n", end_time - start_time);

    // Parallel matrix multiplication using OpenMP
    start_time = omp_get_wtime();
    multiply_matrices(A, B, C, N);
    end_time = omp_get_wtime();
    printf("Parallel time: %f seconds\n", end_time - start_time);

    // Free allocated matrices
    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);

    return 0;
}
