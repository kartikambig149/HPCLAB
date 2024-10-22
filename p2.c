#include <stdio.h>
#include <omp.h>
#include <time.h>

#define N 1000  // Assuming each section can have up to N items

int main() {
    int clothing_count, gaming_count, grocery_count, stationary_count;
    double clothing[N], gaming[N], grocery[N], stationary[N];
    double total_serial = 0, total_parallel = 0;

    // Input: number of items in each section and their prices
    printf("Enter the number of items in the clothing section: ");
    scanf("%d", &clothing_count);
    printf("Enter the prices of items in the clothing section:\n");
    for (int i = 0; i < clothing_count; i++) {
        scanf("%lf", &clothing[i]);
    }

    printf("Enter the number of items in the gaming section: ");
    scanf("%d", &gaming_count);
    printf("Enter the prices of items in the gaming section:\n");
    for (int i = 0; i < gaming_count; i++) {
        scanf("%lf", &gaming[i]);
    }

    printf("Enter the number of items in the grocery section: ");
    scanf("%d", &grocery_count);
    printf("Enter the prices of items in the grocery section:\n");
    for (int i = 0; i < grocery_count; i++) {
        scanf("%lf", &grocery[i]);
    }

    printf("Enter the number of items in the stationery section: ");
    scanf("%d", &stationary_count);
    printf("Enter the prices of items in the stationery section:\n");
    for (int i = 0; i < stationary_count; i++) {
        scanf("%lf", &stationary[i]);
    }

    // Serial execution
    clock_t start_ser = clock();
    
    // Sum the items for each section serially
    for (int i = 0; i < clothing_count; i++) {
        total_serial += clothing[i];
    }
    for (int i = 0; i < gaming_count; i++) {
        total_serial += gaming[i];
    }
    for (int i = 0; i < grocery_count; i++) {
        total_serial += grocery[i];
    }
    for (int i = 0; i < stationary_count; i++) {
        total_serial += stationary[i];
    }

    clock_t end_ser = clock();
    double time_ser = (double)(end_ser - start_ser) / CLOCKS_PER_SEC;

    // Parallel execution
    clock_t start_par = clock();

    #pragma omp parallel for reduction(+:total_parallel)
    for (int i = 0; i < clothing_count; i++) {
        total_parallel += clothing[i];
    }

    #pragma omp parallel for reduction(+:total_parallel)
    for (int i = 0; i < gaming_count; i++) {
        total_parallel += gaming[i];
    }

    #pragma omp parallel for reduction(+:total_parallel)
    for (int i = 0; i < grocery_count; i++) {
        total_parallel += grocery[i];
    }

    #pragma omp parallel for reduction(+:total_parallel)
    for (int i = 0; i < stationary_count; i++) {
        total_parallel += stationary[i];
    }

    clock_t end_par = clock();
    double time_par = (double)(end_par - start_par) / CLOCKS_PER_SEC;

    // Output
    printf("\nSerial Execution:\n");
    printf("Total Bill: %0.2f\n", total_serial);
    printf("Time taken by serial execution: %0.4f seconds\n", time_ser);

    printf("\nParallel Execution:\n");
    printf("Total Bill: %0.2f\n", total_parallel);
    printf("Time taken by parallel execution: %0.4f seconds\n", time_par);

    return 0;
}
