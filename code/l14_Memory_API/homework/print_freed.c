#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int *arry = (int *) malloc(sizeof(int) * 100);

	arry[10] = 1;
	free(arry);
	printf("%d\n", arry[10]);

	return 0;
}
