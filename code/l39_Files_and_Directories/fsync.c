int main(void)
{
	int fd = open("foo", O_CREAT | O_WRONLY | O_TRUNC);
	assert(fd > -1);
	int rc = write(fd, buffer, size);
	assert(rc == size);
	rc = fsync(fd);
	assert(rc == 0);
}
