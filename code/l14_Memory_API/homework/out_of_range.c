#include <stdlib.h>

int main(void)
{
	int *arry = (int *) malloc(sizeof(int) * 100);

	arry[100] = 0;
	free(arry);

	return 0;
}
