#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n;
    float scalar;
    printf("Enter vector size: ");
    scanf("%d", &n);
    printf("Enter scalar value: ");
    scanf("%f", &scalar);

    float *vec = (float*) malloc(n * sizeof(float));
    float *result = (float*) malloc(n * sizeof(float));
    float *result2 = (float*) malloc(n * sizeof(float));

    for (int i = 0; i < n; i++) {
        vec[i] = i * 1.0f;
        
    }
  
    double start = omp_get_wtime();
      for(int i=0;i<n;i++){
        result2[i]=vec[i]+scalar;
    }
    double end2 = omp_get_wtime();
    printf("Time taken for sequential addition: %f seconds\n", end2 - start);
    double start2 = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        result[i] = vec[i] + scalar;
        printf("Thread %d: %f + %f = %f\n", omp_get_thread_num(), vec[i], scalar, result[i]);
    }

    double end = omp_get_wtime();

    printf("Time taken: %f seconds\n", end - start2);

    printf("First 10 results:\n");
    for (int i = 0; i < 10 && i < n; i++) {
        printf("%.2f ", result[i]);
    }
    printf("\n");

    free(vec);
    free(result);
    free(result2);
    return 0;
}
