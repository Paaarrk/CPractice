#define _CRT_SECURE_NO_WARNINGS
#define SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void Init(Q* q)
{
	q->cap = SIZE;
	q->count = 0;
	q->f = 0;
	q->r = 0;
	q->arr = (int*)malloc(sizeof(int) * SIZE);
}

void Destroy(Q* q)
{
	free(q->arr);
}

void IncCap(Q* q)
{
	int newCap = q->cap + SIZE;
	int* newArr = (int*)realloc(q->arr,(sizeof(int) * newCap));
	if (newArr == NULL)
	{
		printf("exit");
		exit(1);
	}
	q->arr = newArr;
	for (int i = q->f; i < q->cap; i++)
	{
		q->arr[i + SIZE] = q->arr[i];
	}
	q->cap = newCap;
	q->f += SIZE;
}

void Enqueue(int d, Q* q)
{
	if ((q->r == q->f) && (q->count != 0))
	{
		IncCap(q);
	}

	q->arr[(q->r)++] = d;
	q->count++;
	if (q->r == q->cap)
		q->r = 0;
}

int Dequeue(Q* q)
{
	if (q->count == 0)
	{
		printf("Empty\n");
		return -1;
	}

	int ret = q->arr[q->f];
	q->arr[(q->f)++] = 0;
	q->count--;
	if (q->f == q->cap)
		q->f = 0;
	return ret;
}

void Info(Q* q)
{
	if (q->count == 0)
	{
		printf("Empty!");
		return;
	}
	int begin = q->f;
	int end = q->r;
	printf("count: %d, [ ", q->count);
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