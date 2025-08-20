#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int num_sizes = 5;

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        double **A = (double**)malloc(n * sizeof(double*));
        double **B = (double**)malloc(n * sizeof(double*));
        double **C = (double**)malloc(n * sizeof(double*));

        for (int i = 0; i < n; i++) {
            A[i] = (double*)malloc(n * sizeof(double));
            B[i] = (double*)malloc(n * sizeof(double));
            C[i] = (double*)malloc(n * sizeof(double));
        }

        // Initialize matrices
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                A[i][j] = i + j;
                B[i][j] = i - j;
            }

        for (int threads = 1; threads <= 8; threads *= 2) {
            double start = omp_get_wtime();

            #pragma omp parallel for num_threads(threads) collapse(2)
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    C[i][j] = A[i][j] + B[i][j];
                }
            }

            double end = omp_get_wtime();
            printf("Matrix size: %d, Threads: %d, Time: %f seconds\n",
                   n, threads, end - start);
        }

        for (int i = 0; i < n; i++) {
            free(A[i]); free(B[i]); free(C[i]);
        }
        free(A); free(B); free(C);
    }

    return 0;
}
