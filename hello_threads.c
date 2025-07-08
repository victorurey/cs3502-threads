#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * TODO: Implement the thread function
 * This function should:
 * - Cast the void pointer argument to a long
 * - Print a message with the thread ID
 * - Return NULL
 */
void *thread_func(void *arg) {
    // TODO: Cast arg to long
    
    // TODO: Print "Hello from thread [ID]"
    
    return NULL;
}

int main(int argc, char *argv[]) {
    // Parse number of threads from command line or use default value of 5
    int n = (argc > 1) ? atoi(argv[1]) : 5;
    
    printf("Creating %d threads...\n", n);
    
    // TODO: Allocate memory for thread handles
    // Remember to check if allocation was successful
    
    // TODO: Create n threads using pthread_create
    // - Pass the thread ID (i) as the argument to thread_func
    // - Check the return value of pthread_create
    // - Handle any errors appropriately
    
    // TODO: Wait for all threads to complete using pthread_join
    // - Check the return value of pthread_join
    // - Handle any errors appropriately
    
    // TODO: Clean up (free allocated memory)
    
    printf("All threads completed successfully\n");
    return EXIT_SUCCESS;
}
