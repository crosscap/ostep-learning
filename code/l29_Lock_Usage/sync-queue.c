#include <stdio.h>
#include <stdlib.h>

#include "../include/common_threads.h"

typedef struct __node_t {
	int value;
	struct __node_t *next;
} node_t;

typedef struct list_t {
	node_t *head;
	node_t *tail;
	pthread_mutex_t headLock;
	pthread_mutex_t tailLock;
} queue_t;

void Queue_Init(queue_t *q)
{
	node_t *tmp = (node_t *)malloc(sizeof(node_t));
	tmp->next = NULL;
	q->head = q->tail = tmp;
	pthread_mutex_init(&q->headLock, NULL);
	pthread_mutex_init(&q->tailLock, NULL);
}

void Queue_Enqueue(queue_t *q, int value)
{
	node_t *tmp = (node_t *)malloc(sizeof(node_t));
	assert(tmp != NULL);
	tmp->value = value;
	tmp->next = NULL;

	Pthread_mutex_lock(&q->tailLock);
	q->tail->next = tmp;
	q->tail = tmp;
	Pthread_mutex_unlock(&q->tailLock);
}

int Queue_Dequeue(queue_t *q, int *value)
{
	Pthread_mutex_lock(&q->headLock);
	node_t *tmp = q->head;
	node_t *newHead = tmp->next;
	if (newHead == NULL) {
		Pthread_mutex_unlock(&q->headLock);
		return -1; // queue was empty
	}
	*value = newHead->value;
	q->head = newHead;
	Pthread_mutex_unlock(&q->headLock);
	free(tmp);
	return 0;
}
