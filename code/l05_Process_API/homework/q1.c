#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int x = 100;

	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		printf("I am child (pid:%d), my x variable is %d.\n",
			(int) getpid(), x);
		x = 42;
		printf("I am child (pid:%d), now my x variable is %d.\n",
			(int) getpid(), x);
	} else {
		printf("I am parent of %d (pid:%d), my x variable is %d.\n",
			rc, (int) getpid(), x);
		x = 81;
		printf("I am parent of %d (pid:%d), now my x variable is %d.\n",
			rc, (int) getpid(), x);
	}
	return 0;
}