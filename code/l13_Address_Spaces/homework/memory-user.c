#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: memory-uer <string>\n");
		exit(1);
	}
	int mega_num = argv[1];
	int using_mega = mega_num * (1 << 20);
	char *arrs = malloc(sizeof(char) * using_mega);
	while (1) {
		for (int i = 0; i < using_mega; ++i) {
			arrs[i]++;
		}
	}
	return 0;
}
