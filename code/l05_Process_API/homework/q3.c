#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int rc = fork();

	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		printf("hello\n");
	} else {
		// int wc = wait(NULL);
		for (int i = 0; i < 1000000; i++) {
			continue;
		} // wait for child to finish
		printf("goodbye\n");
	}

	return 0;
}