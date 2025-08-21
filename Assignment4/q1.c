#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Recursive Fibonacci with OpenMP tasks
long long fib(int n) {
    long long x, y;
    if (n < 2) return n;

    #pragma omp task shared(x)
    x = fib(n - 1);

    #pragma omp task shared(y)
    y = fib(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n; 
    printf("Enter value of n:");
    scanf("%d", &n);
    long long result;
    double start, end;

    omp_set_num_threads(4); // Use 4 threads
    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fib(n);
        }
    }

    end = omp_get_wtime();
    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Time taken = %f seconds\n", end - start);
    return 0;
}
