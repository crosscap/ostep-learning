#include <stdio.h>
#include <sys/time.h>

#include "../../include/common_threads.h"

typedef struct counter_t {
	int value;
} counter_t;

void init(counter_t *c);
void increment(counter_t *c);
void decrement(counter_t *c);
int get(counter_t *c);

int main(void)
{
	struct timeval tv1, tv2;
}

void init(counter_t *c)
{
	c->value = 0;
}

void increment(counter_t *c)
{
	c->value++;
}

void decrement(counter_t *c)
{
	c->value--;
}

int get(counter_t *c)
{
	return c->value;
}
