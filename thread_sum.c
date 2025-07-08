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
    
    // TODO: Initialize partial_sum to 0
    
    // TODO: Sum the assigned portion of the array
    
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
    
    // TODO: Allocate memory for data_array
    // Remember to check if allocation was successful
    
    // TODO: Initialize the array with random values
    
    // Calculate sum using a single thread and measure time
    clock_t start_single = clock();
    long long single_sum = single_threaded_sum();
    clock_t end_single = clock();
    double time_single = (double)(end_single - start_single) / CLOCKS_PER_SEC;
    
    // TODO: Allocate memory for thread handles and thread arguments
    // Remember to check if allocations were successful
    
    // TODO: Calculate chunk size for dividing work among threads
    
    // Start timer for multi-threaded approach
    clock_t start_multi = clock();
    
    // TODO: Create threads and assign work
    // - Set the start_index and end_index for each thread
    // - Make sure the last thread handles any remaining elements
    // - Create each thread with pthread_create
    // - Check return value of pthread_create
    
    // TODO: Wait for all threads to complete using pthread_join
    // - Check return value of pthread_join
    
    // TODO: Combine the partial sums from all threads
    
    // End timer for multi-threaded approach
    clock_t end_multi = clock();
    double time_multi = (double)(end_multi - start_multi) / CLOCKS_PER_SEC;
    
    // Output the results
    printf("Array size: %d\n", ARRAY_SIZE);
    printf("Single-threaded sum: %lld (Time: %.6f seconds)\n", single_sum, time_single);
    printf("Multi-threaded sum: %lld (Time: %.6f seconds)\n", multi_sum, time_multi);
    
    if (single_sum == multi_sum) {
        printf("Results match! Speedup: %.2fx\n", time_single / time_multi);
    } else {
        printf("WARNING: Results do not match! Check your implementation.\n");
    }
    
    // TODO: Clean up (free all allocated memory)
    
    return EXIT_SUCCESS;
}
