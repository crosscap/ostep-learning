#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int *two_vector = (int *) malloc(sizeof(int) * 2);
	int *three_vector;

	two_vector[0] = 1;
	two_vector[1] = 3;
	three_vector = realloc(two_vector, sizeof(int) * 3);
	three_vector[2] = 6;
	free(three_vector);

	return 0;
}
