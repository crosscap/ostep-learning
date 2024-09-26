#include <stdio.h>
#include <stdlib.h>

#include "../include/common_threads.h"

#define BUCKETS (101)

typedef struct node_t {
	int key;
	struct node_t *next;
} node_t;

typedef struct list_t {
	node_t *head;
	pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L);
int List_Insert(list_t *L, int key);
int List_Lookup(list_t *L, int key);

int hash(int key)
{
    return key % BUCKETS;
}

typedef struct __hash_t {
    list_t lists[BUCKETS];
} hash_t;

void Hash_Init(hash_t *H)
{
    int i;
    for (i = 0; i < BUCKETS; i++) {
	List_Init(&H->lists[i]);
    }
}

int Hash_Insert(hash_t *H, int key)
{
    int bucket = hash(key);
    return List_Insert(&H->lists[bucket], key);
}

int Hash_Lookup(hash_t *H, int key)
{
    int bucket = hash(key);
    return List_Lookup(&H->lists[bucket], key);
}
