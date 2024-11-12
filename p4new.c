#include <stdio.h>
#include <omp.h>
#include <time.h>

#define MAX_LIMIT 50  // Maximum terms in Fibonacci series

int fibonacci[MAX_LIMIT];  // Shared array to store Fibonacci numbers
int num_terms;             // Number of terms to generate in the series

void generate_fibonacci_serial() {
    int a = 0, b = 1;
    fibonacci[0] = a;
    fibonacci[1] = b;

    for (int i = 2; i < num_terms; i++) {
        int next = a + b;
        a = b;
        b = next;
        fibonacci[i] = next;
    }
}

void print_fibonacci_serial() {
    for (int i = 0; i < num_terms; i++) {
        printf("%d ", fibonacci[i]);
    }
    printf("\n");
}

int main() {
    printf("Enter the number of terms in the Fibonacci series: ");
    scanf("%d", &num_terms);

    if (num_terms <= 0 || num_terms > MAX_LIMIT) {
        printf("Please enter a valid number between 1 and %d.\n", MAX_LIMIT);
        return 1;
    }

    // Measure serial execution time
    clock_t start, end;
    double serial_time, parallel_time;

    // Serial Execution
    start = clock();
    generate_fibonacci_serial();
    print_fibonacci_serial();
    end = clock();
    serial_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Serial execution time: %f seconds\n", serial_time);

    // Parallel Execution
    start = clock();
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            // Thread 1: Generate Fibonacci series
            int a = 0, b = 1;
            fibonacci[0] = a;
            fibonacci[1] = b;

            for (int i = 2; i < num_terms; i++) {
                int next = a + b;
                a = b;
                b = next;
                fibonacci[i] = next;
            }
        }

        #pragma omp section
        {
            // Thread 2: Print Fibonacci series
            #pragma omp flush(fibonacci)  // Ensure all Fibonacci numbers are generated
            for (int i = 0; i < num_terms; i++) {
                printf("%d ", fibonacci[i]);
            }
            printf("\n");
        }
    }
    end = clock();
    parallel_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Parallel execution time: %f seconds\n", parallel_time);

    // Performance comparison
    printf("Speedup (Serial / Parallel): %f\n", serial_time / parallel_time);

    return 0;
}
