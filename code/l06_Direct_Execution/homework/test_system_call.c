#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define RUNTIME 2000000

int main(void)
{
	int i;
	long time, second, microsecond;
	char buf[100];
	struct timeval tv1, tv2;

	gettimeofday(&tv1, NULL);
	for (i = 0; i < RUNTIME; ++i) {
		read(0, buf, 0);
	}
	gettimeofday(&tv2, NULL);
	second = tv2.tv_sec - tv1.tv_sec;
	microsecond = tv2.tv_usec - tv1.tv_usec;
	time = second * 1000000 + microsecond;
	printf("Time: %ld us\n", time);
	printf("Time per call: %f us\n", (double)time / RUNTIME);

	return 0;
}

