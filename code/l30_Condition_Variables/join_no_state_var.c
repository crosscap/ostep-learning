#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/common.h"
#include "../include/common_threads.h"

pthread_cond_t c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void thr_exit()
{
	Pthread_mutex_lock(&m);
	Pthread_cond_signal(&c);
	Pthread_mutex_unlock(&m);
}

void thr_join()
{
	Pthread_mutex_lock(&m);
	Pthread_cond_wait(&c, &m);
	Pthread_mutex_unlock(&m);
}

void *child(void *arg)
{
	printf("child\n");
	thr_exit();
	return NULL;
}

int main(int argc, char *argv[])
{
	printf("parent: begin\n");
	pthread_t p;
	Pthread_create(&p, NULL, child, NULL);
	thr_join();
	printf("parent: end\n");
	return 0;
}
