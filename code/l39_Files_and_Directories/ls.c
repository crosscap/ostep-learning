int main(int argc, char *argc[])
{
	DIR *dp = open(".");
	assert(dp != NULL);
	struct dirent *d;
	while ((d = readdir(dp)) != NULL) {
		printf("%d %s\n", (int) d->d_ino, d->d_name);
	}
	closedir(dp);

	return 0;
}

struct dirent {
	char           d_name[256]; /* filename */
	ino_t          d_ino;       /* inode number */
	off_t          d_off;       /* offset to the next dirent */
	unsigned short d_reclen;    /* length of this record */
	unsigned char  d_type;      /* type of file */
};
