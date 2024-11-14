#ifndef __QUEUE_H__
#define __QUEUE_H__
typedef struct {
	int* arr;
	int cap;
	int count;
	int f;
	int r;
}Q;

void Init(Q* q);
void Destroy(Q* q);
void IncCap(Q* q);
void Enqueue(int, Q* q);
int Dequeue(Q* q);
void Info(Q* q);

#endif