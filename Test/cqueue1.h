#ifndef __CQUEUE1_H__
#define __CQUEUE1_H__

typedef struct queue1 {
	int cap;
	int count;
	int f;
	int r;
	int* arr;
}Queue1;

void InitQueue1(Queue1*);
void Destroy1(Queue1*);
void IncCap1(Queue1*);
void Enqueue1(int data, Queue1*);
int Dequeue1(Queue1*);
void ShowQueue1(Queue1*);

#endif
