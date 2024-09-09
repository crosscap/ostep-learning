#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int *p = NULL;

	free(p);

	return 0;
}
