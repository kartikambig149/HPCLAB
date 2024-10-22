#include <stdio.h>
#include <omp.h>
#include <time.h>

#define MAX_STUDENTS 1000  // Define maximum number of students

int main() {
    int n;
    double cgpa[MAX_STUDENTS];
    double max_cgpa_serial, max_cgpa_parallel;

    // Input number of students
    printf("Enter the number of students: ");
    scanf("%d", &n);

    // Input CGPAs
    printf("Enter CGPAs of students:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &cgpa[i]);
    }

    // Time measurement for serial execution
    clock_t start_serial = clock();
    // Serial execution: find the maximum CGPA
    max_cgpa_serial = cgpa[0];
    for (int i = 1; i < n; i++) {
        if (cgpa[i] > max_cgpa_serial) {
            max_cgpa_serial = cgpa[i];
        }
    }
    clock_t end_serial = clock();
    double time_serial = (double)(end_serial - start_serial) / CLOCKS_PER_SEC;

    // Time measurement for parallel execution
    clock_t start_parallel = clock();
    // Parallel execution using OpenMP
    max_cgpa_parallel = cgpa[0];
    
    #pragma omp parallel for reduction(max:max_cgpa_parallel)
    for (int i = 1; i < n; i++) {
        if (cgpa[i] > max_cgpa_parallel) {
            max_cgpa_parallel = cgpa[i];
        }
    }
    clock_t end_parallel = clock();
    double time_parallel = (double)(end_parallel - start_parallel) / CLOCKS_PER_SEC;

    // Output results
    printf("Highest CGPA using serial execution: %.2lf\n", max_cgpa_serial);
    printf("Time taken by serial execution: %f seconds\n", time_serial);

    printf("Highest CGPA using parallel execution: %.2lf\n", max_cgpa_parallel);
    printf("Time taken by parallel execution: %f seconds\n", time_parallel);

    return 0;
}
