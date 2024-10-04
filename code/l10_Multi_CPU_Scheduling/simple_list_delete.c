#include <stdlib.h>

typedef struct __Node_t {
	int value;
	struct __Node_t *next;
} Node_t;

Node_t *head = NULL;

int List_Pop()
{
	Node_t *tmp = head;      // remember old head ...
	int value = head->value; // ... and its value
	head = head->next;       // advance head to next pointer
	free(tmp);               // free old head
	return value;            // return value at head
}