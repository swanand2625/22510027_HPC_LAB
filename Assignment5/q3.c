#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 500

int main() {
    int i, j;
    double A[N][N], x[N], y[N];

    
    for (i = 0; i < N; i++) {
        x[i] = i;
        y[i] = 0;
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
        }
    }

    double start = omp_get_wtime();

    #pragma omp parallel for private(i,j) shared(A,x,y)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    double end = omp_get_wtime();
    printf("Matrix-Vector Multiplication completed in %f seconds\n", end - start);

    return 0;
}
