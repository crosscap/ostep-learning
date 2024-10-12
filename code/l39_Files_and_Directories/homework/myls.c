#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>

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
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "-l") == 0) {
				l_flag = 1;
			} else {
				strcpy(folder_name, argv[i]);
			}
		}
	} else {
		fprintf(stderr, "please enter right argument\n");
		exit(1);
	}

	struct stat fileinfo;
	struct dirent *d;
	DIR *dp = opendir(folder_name);
	assert(dp != NULL);

	switch (l_flag) {
	case 0:
		printf("name\n");
		while ((d = readdir(dp)) != NULL) {
			printf("%s\n", d->d_name);
		}
		break;

	case 1:
		printf("file mode\thardlink count\tuser id\tsize\tname\n");
		while ((d = readdir(dp)) != NULL) {
			stat(d->d_name, &fileinfo);
			printf("%x\t%ld\t%d\t%ld\t%s\n",
				fileinfo.st_mode,
				fileinfo.st_nlink,
				fileinfo.st_uid,
				fileinfo.st_size,
				d->d_name);
		}
		break;
	}

	return 0;
}
