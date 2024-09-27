#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/common.h"
#include "../include/common_threads.h"

int done = 0;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *child(void *arg)
{
	printf("child\n");
	Pthread_mutex_lock(&m);
	done = 1;
	Pthread_cond_signal(&c);
	Pthread_mutex_unlock(&m);
	return NULL;
}

int main(int argc, char *argv[])
{
	printf("parent: begin\n");
	pthread_t p;
	Pthread_create(&p, NULL, child, NULL);
	Pthread_mutex_lock(&m);
	while (done == 0)
		Pthread_cond_wait(&c, &m);
	Pthread_mutex_unlock(&m);
	printf("parent: end\n");
	return 0;
}
