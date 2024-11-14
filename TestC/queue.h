#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct {
	int* arr;
	int count;
	int f;
	int r;
	int cap;
}Queue;

void Init(Queue*);
void Destroy(Queue*);
void IncCap(Queue*);
void Enqueue(int, Queue*);
int Dequeue(Queue*);
void Info(Queue*);

#endif

