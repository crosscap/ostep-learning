#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define RUNTIME 2000000

int
main(void)
{
	int i;
	int rc1, rc2;
	int pipe1_to_2[2], pipe2_to_1[2];
	int inbuf[100], outbuf[100];
	long time, second, microsecond;
	struct timeval tv1, tv2;

	if (pipe(pipe1_to_2) || pipe(pipe2_to_1)) {
		fprintf(stderr, "pipe failed\n");
		exit(1);
	}
	gettimeofday(&tv1, NULL);

	rc1 = fork();
	if (rc1 < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc1 == 0) {
		for (i = 0; i < RUNTIME; ++i) {
			write(pipe1_to_2[1], inbuf, 0);
			read(pipe2_to_1[0], outbuf, 0);
		}
	}

	rc2 = fork();
	if (rc2 < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc2 == 0) {
		for (i = 0; i < RUNTIME; ++i) {
			write(pipe2_to_1[1], inbuf, 0);
			read(pipe1_to_2[0], outbuf, 0);
		}
	}

	if (rc1 != 0 && rc2 != 0) {
		waitpid(0, NULL, 0);
		gettimeofday(&tv2, NULL);
		second = tv2.tv_sec - tv1.tv_sec;
		microsecond = tv2.tv_usec - tv1.tv_usec;
		time = second * 1000000 + microsecond;
		printf("Time: %ld us\n", time);
		printf("Time per switch: %f us\n", (double) time / RUNTIME / 2);
	}

	return 0;
}
