#include <stdio.h>
#include <omp.h>

#define N 200   // Vector size
#define SCALAR 5

int main() {
    int i;
    int vector[N], result[N];

    // Initialize vector
    for (i = 0; i < N; i++) {
        vector[i] = i + 1;
    }

    printf("\n=== STATIC schedule with different chunk sizes ===\n");
    for (int chunk = 1; chunk <= 50; chunk *= 2) {
        double start = omp_get_wtime();
        #pragma omp parallel for schedule(static, chunk)
        for (i = 0; i < N; i++) {
            result[i] = vector[i] + SCALAR;
        }
        double end = omp_get_wtime();
        printf("Chunk size %d -> Time: %f sec\n", chunk, end - start);
    }

    printf("\n=== DYNAMIC schedule with different chunk sizes ===\n");
    for (int chunk = 1; chunk <= 50; chunk *= 2) {
        double start = omp_get_wtime();
        #pragma omp parallel for schedule(dynamic, chunk)
        for (i = 0; i < N; i++) {
            result[i] = vector[i] + SCALAR;
        }
        double end = omp_get_wtime();
        printf("Chunk size %d -> Time: %f sec\n", chunk, end - start);
    }

    printf("\n=== Demonstrating nowait clause ===\n");
    double start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (i = 0; i < N/2; i++) {
            result[i] = vector[i] + SCALAR;
        }

        #pragma omp for nowait
        for (i = N/2; i < N; i++) {
            result[i] = vector[i] + SCALAR;
        }
    }
    double end = omp_get_wtime();
    printf("Nowait execution time: %f sec\n", end - start);

    return 0;
}
