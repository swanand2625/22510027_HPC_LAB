#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int compareAsc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int compareDesc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n = 5;
    int vec1[] = {1, 2, 3, 4, 5};
    int vec2[] = {5, 4, 3, 2, 1};
    int result = 0;

    // Sort first vector ascending
    qsort(vec1, n, sizeof(int), compareAsc);

    // Sort second vector descending
    qsort(vec2, n, sizeof(int), compareDesc);

    // Parallel reduction to calculate dot product
    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < n; i++) {
        result += vec1[i] * vec2[i];
    }

    printf("Minimum Scalar Product = %d\n", result);
    return 0;
}
