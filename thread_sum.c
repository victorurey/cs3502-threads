#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/* CONSTANTS */
#define ARRAY_SIZE 1000000

/* GLOBAL VARIABLES */
int *data_array;

/* THREAD ARGUMENT STRUCTURE */
typedef struct {
    int start_index;
    int end_index;
    long long partial_sum;  // To store the result from each thread
} thread_args_t;

/* 
 * TODO: Implement the thread function that calculates partial sum
 * This function should compute the sum of array elements from
 * start_index to end_index-1 and store the result in partial_sum
 */
void *sum_array_portion(void *arg) {
    // TODO: Cast arg to thread_args_t pointer
    thread_args_t *args = (thread_args_t *)arg;

    // TODO: Initialize partial_sum to 0
    args->partial_sum = 0;

    // TODO: Sum the assigned portion of the array
    for (int i = args->start_index; i < args->end_index; ++i) 
    {
        args->partial_sum += data_array[i];
    }

    return NULL;
}

/* Single-threaded sum function for comparison */
long long single_threaded_sum() {
    long long sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += data_array[i];
    }
    return sum;
}

int main(int argc, char *argv[]) {
    // Parse number of threads from command line or use default
    int num_threads = (argc > 1) ? atoi(argv[1]) : 4;
    long long multi_sum = 0;

    printf("Starting array sum with %d threads...\n", num_threads);

    // TODO: Initialize random number generator
    srand(time(NULL));

    // TODO: Allocate memory for data_array
    // Remember to check if allocation was successful
    data_array = malloc(sizeof(int) * ARRAY_SIZE);
    if (data_array == NULL) // Memory error 
    {
        perror("Memory allocation error");
        exit(1);
    }

    // TODO: Initialize the array with random values
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        data_array[i] = rand() % 100;  // Values between 0 and 99
    }

    // Calculate sum using a single thread and measure time
    clock_t start_single = clock();
    long long single_sum = single_threaded_sum();
    clock_t end_single = clock();
    double time_single = (double)(end_single - start_single) / CLOCKS_PER_SEC;

    // TODO: Allocate memory for thread handles and thread arguments
    // Remember to check if allocations were successful
    pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);
    thread_args_t *args = malloc(sizeof(thread_args_t) * num_threads);
    if (threads == NULL || args == NULL) {
        perror("Memory allocation for threads error");
        free(data_array);
        exit(1);
    }

    // TODO: Calculate chunk size for dividing work among threads
    int chunk_size = ARRAY_SIZE / num_threads;

    // Start timer for multi-threaded approach
    clock_t start_multi = clock();

    // TODO: Create threads and assign work
    // - Set the start_index and end_index for each thread
    // - Make sure the last thread handles any remaining elements
    // - Create each thread with pthread_create
    // - Check return value of pthread_create
    for (int i = 0; i < num_threads; ++i) {
        args[i].start_index = i * chunk_size;
        args[i].end_index = (i == num_threads - 1) ? ARRAY_SIZE : (i + 1) * chunk_size;

        int rc = pthread_create(&threads[i], NULL, sum_array_portion, &args[i]);
        if (rc != 0) {
            printf("Error in pthread_create for thread %d", i);
            free(data_array);
            free(threads);
            free(args);
            exit(1);
        }
    }

    // TODO: Wait for all threads to complete using pthread_join
    // - Check return value of pthread_join
    for (int i = 0; i < num_threads; ++i) {
        int rc = pthread_join(threads[i], NULL);
        if (rc != 0) {
            printf("Error in pthread_join for thread %d", i);
            free(data_array);
            free(threads);
            free(args);
            exit(1);
        }

        // TODO: Combine the partial sums from all threads
        multi_sum += args[i].partial_sum;
    }

    // End timer for multi-threaded approach
    clock_t end_multi = clock();
    double time_multi = (double)(end_multi - start_multi) / CLOCKS_PER_SEC;

    // Output the results
    printf("Array size: %d\n", ARRAY_SIZE);
    printf("Single-threaded sum: %lld (Time: %.6f seconds)\n", single_sum, time_single);
    printf("Multi-threaded sum:  %lld (Time: %.6f seconds)\n", multi_sum, time_multi);

    if (single_sum == multi_sum) {
        printf("Results match! Speedup: %.2fx\n", time_single / time_multi);
    } else {
        printf("WARNING: Results do not match! Check your implementation.\n");
    }

    // TODO: Clean up (free all allocated memory)
    free(data_array);
    free(threads);
    free(args);

    return EXIT_SUCCESS;
}
