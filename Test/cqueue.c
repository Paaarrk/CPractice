#include "stdio.h"
#include "stdlib.h"
#include "cqueue.h"

void InitQueue(Queue* q)
{
	q->cap = SIZE;
	q->count = 0;
	q->f = 0;
	q->r = 0;
	q->arr = (int*)malloc(sizeof(int) * q->cap);
}
void IncCap(Queue* q)
{
	int newcap = (q->cap) + SIZE;
	printf("IncCap!! %d to %d\n", (q->cap), newcap);

	int* newArr = (int*)realloc(q->arr, (sizeof(int) * newcap));
	if (newArr == NULL)
	{
		printf("할당 오류\n");
		exit(1);
	}
	q->arr = newArr;
	for (int i = (q->f); i < (q->cap); i++)
	{
		(q->arr)[10 + i] = (q->arr)[i];
		printf("%d %d \n", (q->arr)[i], (q->arr)[i+10]);
	}
	(q->f) += SIZE;
	q->cap = newcap;
}

void Enqueue(int data, Queue* q)
{
	if (((q->f) == (q->r)) && ((q->count) != 0))
	{
		IncCap(q);
	}
	q->arr[(q->r)++] = data;
	if (q->r == q->cap)
		q->r = 0;
	(q->count)++;
	printf("f: %d, r: %d \n", q->f, q->r);
}
int Dequeue(Queue* q)
{
	int ret;
	if (q->count == 0)
	{
		printf("Queue is Empty!!\n");
		return 0;
	}
	ret = q->arr[(q->f)];
	q->arr[(q->f)] = 0;
	(q->f) += 1;
	if (q->f == q->cap)
		q->f = 0;
	(q->count)--;
	printf("f: %d, r: %d \n", q->f, q->r);
	return ret;
}

void ShowQueue(Queue* q)
{
	if (q->count == 0)
	{
		printf("Empty\n");
		return;
	}

	
	int begin = (q->f);
	int end = (q->r);
	printf("[ ");
	while (1)
	{
		printf("%d ", q->arr[begin]);
		begin++;
		if (begin == (q->cap))
			begin = 0;
		if (begin == end)
			break;
	}
	printf("]\n");
}
