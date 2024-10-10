int main(void)
{
	int fd = open("foo.txt.tmp", O_WRONLY | O_CREAT | O_TRUNC);
	write(fd, buffer, size); // write out new version of file
	fsync(fd);
	close(fd);
	rename("foo.txt.tmp", "foo.txt");
}
