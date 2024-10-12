#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>

#define BUFFSIZE 256

int main(int argc, const char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "please enter right number of parameter!\n");
		exit(1);
	}

	char char_in_file;
	char buffer[BUFFSIZE];
	char to_int_temp[10];
	strcpy(to_int_temp, &argv[1][1]);
	int tail_num = atoi(to_int_temp);
	const char *filename = argv[2];
	struct stat fileinfo;
	int rc = stat(filename, &fileinfo);
	assert(rc == 0);
	off_t file_size = fileinfo.st_size;
	int fd = open(filename, O_RDONLY);
	assert(fd != -1);
	off_t offset = lseek(fd, file_size - 1, SEEK_SET);
	off_t last_break = offset;
	int break_cnt = 0;

	read(fd, &char_in_file, 1);
	if (char_in_file == '\n') {
		last_break = offset;
		offset = lseek(fd, offset - 1, SEEK_SET);
	} else {
		last_break = file_size;
	}
	while (break_cnt < tail_num) {
		rc = read(fd, &char_in_file, 1);
		assert(rc > -1);
		if (char_in_file == '\n') {
			break_cnt++;
			lseek(fd, offset + 1, SEEK_SET);
			rc = read(fd, buffer, last_break - offset);
			assert(rc > -1);
			buffer[rc] = '\0';
			write(1, buffer, rc);
			if (break_cnt == 1 && last_break == file_size) {
				write(1, "\n", 1);
			}
			last_break = offset;
		}
		offset = lseek(fd, offset - 1, SEEK_SET);
	}

	close(fd);
	return 0;
}
