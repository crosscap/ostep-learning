#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>

#define MAX_QUEUE_SIZE 1000

typedef struct {
	DIR *folders[MAX_QUEUE_SIZE];
	int front;
	int rear;
} queue;

int queue_empty(queue *);
void queue_init(queue *);
void enqueue(queue *, DIR *);
DIR *dequeue(queue *);

int main(int argc, const char *argv[])
{
	queue q;
	char folder_name[256];
	struct stat fileinfo;
	int rc;

	if (argc == 1) {
		strcpy(folder_name, ".");
	} else if (argc == 2) {
		strcpy(folder_name, argv[1]);
	} else {
		fprintf(stderr, "please enter a folder's name!\n");
		exit(1);
	}
	queue_init(&q);

	DIR *dp = opendir(folder_name);
	DIR *new_dp;
	assert(dp != NULL);
	struct dirent *d;

	enqueue(&q, dp);
	while (!queue_empty(&q)) {
		dp = dequeue(&q);
		while ((d = readdir(dp)) != NULL) {
			printf("%s\n", d->d_name);
			rc = stat(d->d_name, &fileinfo);
			assert(rc == 0);
			if (S_ISDIR(fileinfo.st_mode)) {
				new_dp = opendir(d->d_name);
				enqueue(&q, new_dp);
			}
		}
		closedir(dp);
	}

	return 0;
}



int queue_empty(queue *q)
{
	return q->front == q->rear;
}

void queue_init(queue *q)
{
	q->front = 0;
	q->rear = 0;
}

void enqueue(queue *q, DIR *dir)
{
	q->folders[q->rear] = dir;
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
}

DIR *dequeue(queue *q)
{
	DIR *res = q->folders[q->front];
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return res;
}
