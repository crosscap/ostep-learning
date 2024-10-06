#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

typedef struct __ns_mutex_t {
	sem_t mutex;
} ns_mutex_t;

void ns_mutex_init(ns_mutex_t *m)
{
	sem_init(&m->mutex, 0, 1);
}

void ns_mutex_acquire(ns_mutex_t *m)
{
	sem_wait(&m->mutex);
}

void ns_mutex_release(ns_mutex_t *m)
{
	sem_post(&m->mutex);
}

void *worker(void *arg)
{
	return NULL;
}

int main(int argc, char *argv[])
{
	printf("parent: begin\n");
	printf("parent: end\n");
	return 0;
}
