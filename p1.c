#include <stdio.h>
#include <omp.h>
#include <time.h>
#define N 1000

int main() {
    int n;
    double A[N][N], x[N], y[N];
    
    // Input size of matrix
    scanf("%d", &n);
    
    // Input matrix A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);  // Use %lf for double
        }
    }
    
    // Input vector x
    for (int i = 0; i < n; i++) {
        scanf("%lf", &x[i]);  // Use %lf for double
    }

    // Serial execution
    clock_t start_ser = clock();
    for (int i = 0; i < n; i++) {
        y[i] = 0;
        for (int j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    clock_t end_ser = clock();
    double time_ser = (double)(end_ser - start_ser) / CLOCKS_PER_SEC;
    
    // Display results of serial execution
    printf("Result of multiplication using serial execution:\n");
    for (int i = 0; i < n; i++) {
        printf("%f ", y[i]);  // Use %f for double
    }
    printf("\nTime taken by serial execution: %0.2f seconds\n", time_ser);

    // Parallel execution
    clock_t start_par = clock();
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        y[i] = 0;
        for (int j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    clock_t end_par = clock();
    double time_par = (double)(end_par - start_par) / CLOCKS_PER_SEC;

    // Display results of parallel execution
    printf("Result of multiplication using parallel execution:\n");
    for (int i = 0; i < n; i++) {
        printf("%f ", y[i]);  // Use %f for double
    }
    printf("\nTime taken by parallel execution: %0.2f seconds\n", time_par);

    return 0;
}
