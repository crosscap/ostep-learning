#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/common.h"
#include "../include/common_threads.h"

int loops;
int buffer;
int count = 0;

pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int consumers = 1;
int verbose = 1;

void put(int value)
{
	assert(count == 0);
	count = 1;
	buffer = value;
}

int get()
{
	assert(count == 1);
	count = 0;
	return buffer;
}

void *producer(void *arg)
{
	int i;
	for (i = 0; i < loops; i++) {
		Mutex_lock(&mutex);
		while (count == 1)
			Cond_wait(&empty, &mutex);
		put(i);
		Cond_signal(&fill);
		Mutex_unlock(&mutex);
	}

	return NULL;
}

void *consumer(void *arg)
{
	int tmp = 0;
	// consumer: keep pulling data out of shared buffer
	// until you receive a -1 (end-of-production marker)
	while (tmp != -1) {
		Mutex_lock(&mutex);               // c1
		while (count == 0)                // c2
			Cond_wait(&fill, &mutex); // c3
		tmp = get();                      // c4
		Cond_signal(&empty);              // c5
		Mutex_unlock(&mutex);             // c6
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "usage: %s <buffersize> <loops> <consumers>\n", argv[0]);
		exit(1);
	}
	loops = atoi(argv[1]);
	consumers = atoi(argv[2]);

	int i;
	pthread_t pid, cid[consumers];
	Pthread_create(&pid, NULL, producer, NULL);
	for (i = 0; i < consumers; i++) {
		Pthread_create(&cid[i], NULL, consumer, (void *) (long long int) i);
	}
	Pthread_join(pid, NULL);
	for (i = 0; i < consumers; i++) {
		Pthread_join(cid[i], NULL);
	}
	return 0;
}
