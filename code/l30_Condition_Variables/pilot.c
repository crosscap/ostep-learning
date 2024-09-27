#include <stdlib.h>
#include <pthread.h>

#include "../include/common_threads.h"

#define MAX_HEAP_SIZE 1024 * 1024 // 1MB

// how many bytes of the heap are free?
int bytesLeft = MAX_HEAP_SIZE;

// need lock and condition too
pthread_cond_t c;
pthread_mutex_t m;

void *allocate(int size)
{
	Pthread_mutex_lock(&m);
	while (bytesLeft < size)
		Pthread_cond_wait(&c, &m);
	void *ptr = malloc(MAX_HEAP_SIZE); // get mem from heap
	bytesLeft -= size;
	Pthread_mutex_unlock(&m);
	return ptr;
}

void local_free(void *ptr, int size)
{
	Pthread_mutex_lock(&m);
	bytesLeft += size;
	free(ptr);
	Pthread_cond_signal(&c); // whom to signal??
	Pthread_mutex_unlock(&m);
}
