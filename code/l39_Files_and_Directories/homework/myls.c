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
	int l_flag = strcmp(argv[1], "-l") == 0 ? 1 : 0;
	const char *folder_name = argv[2];
	struct stat fileinfo;

	int rc = stat(filename, &fileinfo);
	assert(rc == 0);



	return 0;
}
