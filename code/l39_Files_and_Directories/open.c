int main(void)
{
	int fd = open("foo", O_CREAT | O_WRONLY | O_TRUNC);
	return 0;
}
