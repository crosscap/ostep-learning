#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	int l_flag = 0;
	char folder_name[256];

	if (argc == 1) {
		strcpy(folder_name, ".");
	} else if (argc == 2) {
		if (strcmp(argv[1], "-l") == 0) {
			l_flag = 1;
			strcpy(folder_name, ".");
		} else {
			strcpy(folder_name, argv[1]);
		}
	} else if (argc == 3) {
	} else {
		fprintf(stderr, "please enter right argument\n");
		exit(1);
	}

	struct stat fileinfo;

	int rc = stat(filename, &fileinfo);
	assert(rc == 0);



	return 0;
}
