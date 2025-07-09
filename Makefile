CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: hello_threads thread_sum

hello_threads: hello_threads.c
	$(CC) $(CFLAGS) $< -o $@
thread_sum: thread_sum.c
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -f hello_threads thread_sum
