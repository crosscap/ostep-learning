#include <stdio.h>
#include <stdlib.h>

#include "../include/common_threads.h"

// basic node structure
typedef struct node_t {
	int key;
	struct node_t *next;
} node_t;

typedef struct list_t {
	node_t *head;
	pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L)
{
	L->head = NULL;
	pthread_mutex_init(&L->lock, NULL);
}

int List_Insert(list_t *L, int key)
{
	Pthread_mutex_lock(&L->lock);
	node_t *new = (node_t *)malloc(sizeof(node_t));
	if (new == NULL) {
		perror("malloc");
		Pthread_mutex_unlock(&L->lock);
		return -1; // fail
	}
	new->key = key;
	new->next = L->head;
	L->head = new;
	Pthread_mutex_unlock(&L->lock);
	return 0; // success
}

int List_Lookup(list_t *L, int key)
{
	Pthread_mutex_lock(&L->lock);
	node_t *curr = L->head;
	while (curr) {
		if (curr->key == key) {
			Pthread_mutex_unlock(&L->lock);
			return 0; // success
		}
		curr = curr->next;
	}
	Pthread_mutex_unlock(&L->lock);
	return -1; // failure
}
