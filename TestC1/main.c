#include <stdio.h>
#include "time.h"
#include "stdlib.h"
#include "queue.h"

void TestQ()
{
	int count = 0;
	Q q;
	Init(&q);

	while (count < 100)
	{
		Enqueue((rand() % 200), &q);
		Info(&q);
		count++;
	}
	while (count > 50)
	{
		printf("out: %d ->", Dequeue(&q));
		Info(&q);
		count--;
	}
	while (count < 20)
	{
		Enqueue((rand() % 200), &q);
		Info(&q);
		count++;
	}
	while (q.count != 0)
	{
		printf("out: %d \n", Dequeue(&q));
		Info(&q);
	}
}

int main()
{
	srand(time(NULL));

	TestQ();
	return 0;
}