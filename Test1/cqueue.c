#define _CRT_SECURE_NO_WARNINGS
#define SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include "cqueue.h"
void InitQueue1(Queue1* q)
{
	q->cap = SIZE;
	q->count = 0;
	q->f = 0;
	q->r = 0;
	q->arr = (int*)malloc(sizeof(int) * SIZE);
}

void Destroy1(Queue1* q)
{
	free(q->arr);
}

void IncCap1(Queue1* q)
{
	printf("inc cap: %d to %d \n", q->cap, q->cap + SIZE);
	int* newArr = (int*)realloc(q->arr, sizeof(int) * (SIZE + (q->cap)));
	if (newArr == NULL)
	{
		printf("할당 오류");
		exit(1);
	}
	q->arr = newArr;

	for (int i = q->f; i < q->cap; i++)
	{
		q->arr[i + SIZE] = q->arr[i];
	}
	q->cap += SIZE;
	q->f += SIZE;
}

void Enqueue1(int data, Queue1* q)
{
	if (q->f == q->r && q->count != 0)
	{
		IncCap1(q);
	}

	q->arr[(q->r)++] = data;
	if (q->r == q->cap)
		q->r = 0;
	q->count++;
}

int Dequeue1(Queue1* q)
{
	if (q->count == 0)
	{
		printf("Empty Queue\n");
		exit(1);
	}
	int ret = q->arr[q->f];
	q->arr[(q->f)++] = 0;
	if (q->f == q->cap)
		q->f = 0;
	q->count--;
	return ret;
}

void ShowQueue1(Queue1* q)
{
	int begin = q->f;
	int end = q->r;
	if (q->count == 0)
	{
		printf("EmptyList\n");
		return;
	}
	printf("f: %d, r: %d, [ ", begin, end);
	while (1)
	{
		if (begin == end)
			break;
		printf("%d ", q->arr[begin]);
		begin++;
		if (begin == q->cap)
			begin = 0;
	}
	printf("] count: %d \n", q->count);
}