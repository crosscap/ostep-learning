#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int *arry = (int *) malloc(sizeof(int) * 100);

	free(&arry[10]);

	return 0;
}
