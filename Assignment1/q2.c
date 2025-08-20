#include <stdio.h>
#include <omp.h>

int main() {
    int n;

    printf("Enter number of threads: ");
    scanf("%d", &n);

    
    printf("\nSequential Execution:\n");
    for (int i = 0; i < n; i++) {
        printf("Hello, World from thread %d\n", i);
    }

    
    printf("\nParallel Execution:\n");
    omp_set_num_threads(n);
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Hello, World from thread %d\n", tid);
    }

    return 0;
}
