#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 500

int main() {
    int i, j;
    double A[N][N], scalar = 5.0;

    
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            A[i][j] = i + j;

    double start = omp_get_wtime();

    #pragma omp parallel for private(i,j) shared(A,scalar)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = scalar * A[i][j];
        }
    }

    double end = omp_get_wtime();
    printf("Matrix-Scalar Multiplication completed in %f seconds\n", end - start);

    return 0;
}
