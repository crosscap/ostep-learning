#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/common.h"
#include "../include/common_threads.h"

int done = 0;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thr_exit()
{
	done = 1;
	Pthread_cond_signal(&c);
}

void thr_join()
{
	if (done == 0) {
		// Pthread_cond_wait(&c);
	}
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
