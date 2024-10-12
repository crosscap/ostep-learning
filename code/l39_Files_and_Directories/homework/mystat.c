#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/unistd.h>

int main(int argc, const char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "please enter a file or folder's name!\n");
		exit(1);
	}

	const char *filename = argv[1];
	struct stat fileinfo;

	int rc = stat(filename, &fileinfo);
	assert(rc == 0);

	printf("file type: %d\n", fileinfo.st_mode);
	printf("file size: %ld B\n", fileinfo.st_size);
	printf("number of 512B blocks allocated: %ld\n", fileinfo.st_blocks);
	printf("referenced counter: %ld\n", fileinfo.st_nlink);

	return 0;
}
