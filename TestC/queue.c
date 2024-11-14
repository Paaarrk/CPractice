#define SIZE 10
#include "queue.h"
#include "stdio.h"
#include "stdlib.h"


void Init(Queue* q)
{
	q->count = 0;
	q->f = 0;
	q->r = 0;
	q->cap = SIZE;
	q->arr = (int*)malloc(sizeof(int) * q->cap);
}

void Destroy(Queue* q)
{
	free(q->arr);
}

void IncCap(Queue* q)
{
	int newCap = SIZE + (q->cap);
	Queue* temp = (int*)realloc(q->arr, (sizeof(int) * newCap));
	if (temp == NULL)
	{
		printf("Realloc Failed");
		exit(1);
	}

	q->arr = temp;
	for (int i = q->f; i < q->cap; i++)
	{
		q->arr[i + SIZE] = q->arr[i];
	}
	(q->cap) = newCap;
	(q->f) += SIZE;
}

void Enqueue(int d, Queue* q)
{
	if ((q->r == q->f) && (q->count != 0))
	{
		IncCap(q);
	}

	q->arr[(q->r)++] = d;
	(q->count)++;
	if (q->r == q->cap)
		q->r = 0;
}

int Dequeue(Queue* q)
{
	if (q->count == 0)
	{
		printf("Empty\n");
		return 0;
	}
	int ret = q->arr[q->f];
	q->arr[(q->f)++] = 0;
	if (q->f == q->cap)
		q->f = 0;
	(q->count)--;
	return ret;
}

void Info(Queue* q)
{
	if (q->count == 0)
	{
		printf("Empty\n");
		return;
	}
	int begin = q->f;
	int end = q->r;
	printf("[ ");
	while (1)
	{
		printf("%d ", q->arr[begin]);
		begin++;
		if (begin == q->cap)
			begin = 0;
		if (begin == end)
			break;
	}
	printf("] \n");
}