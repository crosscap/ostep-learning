#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int fd = open("./file.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	int rc = fork();

	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		write(fd, "hello, I am child\n", 18);
	} else {
		write(fd, "hello, I am parent\n", 19);
	}
	close(fd);

	return 0;
}
