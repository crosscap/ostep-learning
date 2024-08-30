#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{


	int fd[2];
	char buf[100];

	if (pipe(fd)) {
		fprintf(stderr, "pipe failed\n");
		exit(1);
	}

	int rc1 = fork();
	if (rc1 < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc1 == 0) {
		printf("this is rc1\n");
		read(fd[0], buf, 5);
		printf("%s\n", buf);
		return 0;
	}

	int rc2 = fork();
	if (rc2 < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc2 == 0) {
		write(fd[1], "hello", 5);
		printf("this is rc2\n");
		return 0;
	} else {
		printf("goodbye\n");
	}

	return 0;
}