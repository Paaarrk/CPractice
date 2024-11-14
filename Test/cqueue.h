#ifndef __CQUEUE_H__
#define __CQUEUE_H__
#define SIZE 10;
typedef struct queue
{
	int cap;
	int count;
	int f;
	int r;
	int* arr;
}Queue;

void InitQueue(Queue*);
void IncCap(Queue*);
void Enqueue(int, Queue*);
int Dequeue(Queue*);
void ShowQueue(Queue*);

#endif
