#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    long long int num_points;
    printf("Enter number of points: ");
    scanf("%lld", &num_points);

    long long int count = 0;

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        unsigned int seed = time(NULL) ^ omp_get_thread_num();
        long long int local_count = 0;

        #pragma omp for
        for (long long int i = 0; i < num_points; i++) {
            double x = (double) rand_r(&seed) / RAND_MAX;
            double y = (double) rand_r(&seed) / RAND_MAX;
            if (x*x + y*y <= 1.0) {
                local_count++;
            }
        }

        #pragma omp atomic
        count += local_count;
    }

    double pi = (4.0 * count) / num_points;
    double end = omp_get_wtime();

    printf("Estimated Pi = %f\n", pi);
    printf("Time taken: %f seconds\n", end - start);

    return 0;
}
