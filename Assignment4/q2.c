#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 5 
#define ITEMS 3  

int buffer[N];
int count = 0;  

int main() {
    int i, item;

    #pragma omp parallel sections shared(buffer, count)
    {
        // Producer
        #pragma omp section
        {
            for (i = 0; i < ITEMS; i++) {
                item = i + 1; // Produce item

                #pragma omp critical
                {
                    while (count == N) {
                        // Buffer full, wait
                    }
                    buffer[count] = item;
                    count++;
                    printf("Produced: %d (Buffer count: %d)\n", item, count);
                }
            }
        }

        // Consumer
        #pragma omp section
        {
            for (i = 0; i < ITEMS; i++) {
                int consumed;

                #pragma omp critical
                {
                    while (count == 0) {
                        // Buffer empty, wait
                    }
                    consumed = buffer[count - 1];
                    count--;
                    printf("Consumed: %d (Buffer count: %d)\n", consumed, count);
                }
            }
        }
    }

    return 0;
}
