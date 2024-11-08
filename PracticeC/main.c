#include <stdlib.h>

#define SIZE 10
/*
C 스타일 전역함수로 QUEUE 만들기
*/

typedef struct queue {
	int count;
	int capacity;
	int front;
	int rear;
	int* arr;
}Queue;

static void QueueInit(Queue* q)
{
	q->count = 0;
	q->capacity = SIZE;
	q->front = 0;
	q->rear = 0;
	q->arr = (int*)calloc(sizeof(int), (SIZE));
}

static void IncCapacity(Queue* q)
{
	if ((q->rear) == (q->front))
	{
		printf("IncCap\n");
		int len = (q->capacity) - (q->front);
		(q->capacity) += SIZE;
		int* newArr = (int* )realloc((q->arr), sizeof(int) * (q->capacity));
		if (newArr == NULL)
		{
			printf("메모리 할당 실패");
			free(q);
			exit(1);
		}
		(q->arr) = newArr;
		
		// [1][r][][][f][x][x][][][][][][] => [1][r][][][][][][][][f][x][x]
		for (int i = 0; i < len; i++)
		{
			(q->arr)[(q->front) + SIZE + i] = (q->arr)[(q->front) + i];
			q->arr[(q->front) + i] = 0;
		}
		q->front += SIZE;
		printf("현재 f의 위치 %d, 현재 r의 위치 %d\n", q->front, q->rear);
	}
}
static void Enqueue(Queue* q, int x)
{
	(q->arr)[q->rear] = x;
	(q->rear) += 1;
	if ((q->rear) == q->capacity)
		q->rear = 0;
	(q->count)++;
	printf("현재 f의 위치 %d, 현재 r의 위치 %d\n", q->front, q->rear);
	IncCapacity(q);
}

static int Dequeue(Queue* q)
{
	int ret = q->arr[q->front];
	q->arr[q->front] = 0;
	(q->front)++;
	if (q->front == q->capacity)
		q->front = 0;
	printf("현재 f의 위치 %d, 현재 r의 위치 %d\n", q->front, q->rear);
	return ret;
}

static void QueueDelete(Queue* q)
{
	free(q->arr);
}

static void QueueInfo(Queue* q)
{
	int begin = q->front;
	int end = q->rear;
	printf("[front]");
	while (1)
	{
		if (begin == end)
			break;
		printf("[%d]", (q->arr)[begin]);
		begin++;
		if (begin == (q->capacity))
			begin = 0;
	}
	printf("[end]\n");
}

int main(void)
{
	Queue queue;
	
	QueueInit(&queue);
	for (int i = 1; i <= 14; i++)
	{
		Enqueue(&queue, i);
		QueueInfo(&queue);
	}
	for (int i = 0; i < 3; i++)
	{
		printf("%d \n", Dequeue(&queue));
		QueueInfo(&queue);
	}
	for (int i = 1; i <= 40; i++)
	{
		Enqueue(&queue, 100 + i);
		QueueInfo(&queue);
	}
	for (int i = 1; i <= 20; i++)
	{
		Dequeue(&queue);
		QueueInfo(&queue);
	}

	QueueDelete(&queue);
}