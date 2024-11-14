#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "queue.h"

void TestQueue()
{
	int c = 0;
	Queue q;
	Init(&q);

	while (c < 100)
	{
		Enqueue((rand() % 400), &q);
		Info(&q);
		c++;
	}
	while (c > 50)
	{
		printf("out: %d \n", Dequeue(&q));
		Info(&q);
		c--;
	}
	while (c < 70)
	{
		Enqueue((rand() % 400), &q);
		Info(&q);
		c++;
	}
	while ((q.count) != 0)
	{
		printf("out: %d \n", Dequeue(&q));
		Info(&q);
		c--;
	}

	Destroy(&q);
}

int main (void)
{
	srand(time(NULL));

	TestQueue();
	return 0;
}