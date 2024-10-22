#include <stdio.h>
#include <omp.h>
#include <time.h>

#define NUM_STEPS 1000000  // The higher the steps, the more accurate Pi is

int main() {
    int i;
    double pi_serial = 0.0, pi_parallel = 0.0;
    double step = 1.0 / (double)NUM_STEPS; // Step size for integration

    // Serial execution
    clock_t start_serial = clock();
    for (i = 0; i < NUM_STEPS; i++) {
        double x = (i + 0.5) * step;   // Midpoint of each step
        pi_serial += 4.0 / (1.0 + x * x);  // Function value at midpoint
    }
    pi_serial *= step;
    clock_t end_serial = clock();
    double time_serial = (double)(end_serial - start_serial) / CLOCKS_PER_SEC;

    // Parallel execution using OpenMP
    clock_t start_parallel = clock();

    #pragma omp parallel for reduction(+:pi_parallel)
    for (i = 0; i < NUM_STEPS; i++) {
        double x = (i + 0.5) * step;  // Midpoint of each step
        pi_parallel += 4.0 / (1.0 + x * x);  // Function value at midpoint
    }
    pi_parallel *= step;

    clock_t end_parallel = clock();
    double time_parallel = (double)(end_parallel - start_parallel) / CLOCKS_PER_SEC;

    // Output results
    printf("Pi computed using serial execution: %.15f\n", pi_serial);
    printf("Time taken by serial execution: %f seconds\n", time_serial);

    printf("Pi computed using parallel execution: %.15f\n", pi_parallel);
    printf("Time taken by parallel execution: %f seconds\n", time_parallel);

    return 0;
}
