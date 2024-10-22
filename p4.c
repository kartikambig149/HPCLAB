#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define MAX 1000 // Define maximum size for the Fibonacci series

int fib[MAX];  // Array to store Fibonacci numbers
int n;         // Number of terms in Fibonacci series
omp_lock_t lock; // Lock for synchronization

// Function to generate the Fibonacci series
void generate_fibonacci() {
    fib[0] = 0;
    fib[1] = 1;
    
    // Generate the Fibonacci numbers
    for (int i = 2; i < n; i++) {
        omp_set_lock(&lock); // Acquire lock before modifying the array
        fib[i] = fib[i - 1] + fib[i - 2];
        omp_unset_lock(&lock); // Release lock after updating the array
    }
}

// Function to print the Fibonacci series
void print_fibonacci() {
    // Print the Fibonacci numbers
    for (int i = 0; i < n; i++) {
        omp_set_lock(&lock); // Acquire lock before accessing the array
        printf("%d ", fib[i]);
        omp_unset_lock(&lock); // Release lock after accessing the array
    }
    printf("\n");
}

int main() {
    printf("Enter the number of Fibonacci terms: ");
    scanf("%d", &n);
    
    if (n > MAX) {
        printf("Limit exceeded! Max supported is %d.\n", MAX);
        return 1;
    }
    
    // Initialize the OpenMP lock
    omp_init_lock(&lock);
    
    // Time measurement
    double start_serial, end_serial, start_parallel, end_parallel;

    // Serial execution (single thread for both generation and printing)
    start_serial = omp_get_wtime();  // Start time
    generate_fibonacci();
    print_fibonacci();
    end_serial = omp_get_wtime();    // End time
    printf("Time taken by serial execution: %f seconds\n", end_serial - start_serial);

    // Parallel execution using OpenMP
    start_parallel = omp_get_wtime(); // Start time for parallel execution

    #pragma omp parallel sections
    {
        // One thread generates the Fibonacci series
        #pragma omp section
        {
            generate_fibonacci();
        }

        // Another thread prints the Fibonacci series
        #pragma omp section
        {
            print_fibonacci();
        }
    }

    end_parallel = omp_get_wtime();   // End time for parallel execution
    printf("Time taken by parallel execution: %f seconds\n", end_parallel - start_parallel);

    // Destroy the OpenMP lock
    omp_destroy_lock(&lock);

    return 0;
}
