#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

pthread_mutex_t printLock = PTHREAD_MUTEX_INITIALIZER;
long currentIndex = 0;


/*
 * TODO: Implement the thread function
 * This function should:
 * - Cast the void pointer argument to a long
 * - Print a message with the thread ID
 * - Return NULL
 */
void *thread_func(void *arg) {
    // TODO: Cast arg to long
    long newId = (long)arg;
    // TODO: Print "Hello from thread [ID]"
    // Implementation of mutex function to print threads in order
    while(1)
    {
	pthread_mutex_lock(&printLock);
	if (newId == currentIndex) // Thread creation matches mutex position
	{
		printf("Thread %ld\n", newId);
		currentIndex++;
		pthread_mutex_unlock(&printLock);
		break;
	}
	pthread_mutex_unlock(&printLock);
	sched_yield();
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    // Parse number of threads from command line or use default value of 5
    int n = (argc > 1) ? atoi(argv[1]) : 5;
    
    printf("Creating %d threads...\n", n);
    
    // TODO: Allocate memory for thread handles
    // Remember to check if allocation was successful
    pthread_t *threads = malloc(n * sizeof(pthread_t));
    if (threads == NULL) // Error check
    {
        perror("Memory allocation error");
        exit(1);
    }

    // TODO: Create n threads using pthread_create
    // - Pass the thread ID (i) as the argument to thread_func
    // - Check the return value of pthread_create
    // - Handle any errors appropriately
    for (long i = 0; i < n; ++i)
    {
        int rc = pthread_create(&threads[i], NULL, thread_func, (void *)i);
        if (rc != 0) // Error in pthread_create
        {
            printf("Error in creation of thread %ld", i);
            free(threads); // Memory leak prevention
            exit(1);
        }
    }
    // TODO: Wait for all threads to complete using pthread_join
    // - Check the return value of pthread_join
    // - Handle any errors appropriately
    for (int i = 0; i < n; ++i)
    {
        int rc = pthread_join(threads[i], NULL);
        if (rc != 0) // Error in pthread_join
        {
            printf("Error in thread join %d", i);
            free(threads);
            exit(1);
        }
    }

    // TODO: Clean up (free allocated memory)
    free(threads);
    pthread_mutex_destroy(&printLock); 
    printf("All threads completed successfully\n");
    return EXIT_SUCCESS;
}
