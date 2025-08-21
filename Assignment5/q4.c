#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000

int main() {
    int i;
    int arr[N], prefix[N];

   
    for (i = 0; i < N; i++)
        arr[i] = 1;  

    double start = omp_get_wtime();

    prefix[0] = arr[0];
    #pragma omp parallel for
    for (i = 1; i < N; i++) {
        prefix[i] = prefix[i-1] + arr[i]; 
    }

    double end = omp_get_wtime();
    printf("Prefix sum completed in %f seconds, last prefix value = %d\n",
           end - start, prefix[N-1]);

    return 0;
}
