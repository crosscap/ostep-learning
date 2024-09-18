#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define PAGESIZE   4096
#define PAGEMAXNUM 16384

// Please check this answer! I am not sure about it.

int
main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "please enter right num of argument!\n");
		exit(1);
	}
	int *a;
	int jump = PAGESIZE / sizeof(int);
	int num_pages = atoi(argv[1]);
	int try_times = atoi(argv[2]);
	struct timeval tv1, tv2;
	int second, microsecond, time;
	int i, j;

	a = (int *) malloc(PAGESIZE * PAGEMAXNUM);

	gettimeofday(&tv1, NULL);
	for (i = 0; i < try_times; ++i) {
		for (j = 0; j < num_pages * jump; j += jump) {
			a[j] += 1;
		}
	}
	gettimeofday(&tv2, NULL);
	second = tv2.tv_sec - tv1.tv_sec;
	microsecond = tv2.tv_usec - tv1.tv_usec;
	time = second * 1000000 + microsecond;
	printf("Time per access: %f ns in %d times of access\n",
	       (double) time / (try_times * num_pages) * 1000, num_pages);
	free(a);

	return 0;
}
