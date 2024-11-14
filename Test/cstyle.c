#include "cstyle.h"
//#include "cqueue.h"
#include "cqueue1.h"



//void CStyle0()
//{
//	Queue q;
//	InitQueue(&q);
//
//	for (int i = 0; i < 46; i++)
//	{
//		Enqueue(i, &q);
//	}
//	ShowQueue(&q);
//	for (int i = 0; i < 46; i++)
//	{
//		Dequeue(&q);
//	}
//	ShowQueue(&q);
//	for (int i = 25; i < 57; i++)
//	{
//		Enqueue(i, &q);
//	}
//	ShowQueue(&q);
//}

void CStyle1()
{
	Queue1 q;
	InitQueue1(&q);

	for (int i = 0; i < 46; i++)
	{
		Enqueue(i, &q);
	}
	ShowQueue1(&q);
	for (int i = 0; i < 46; i++)
	{
		Dequeue1(&q);
	}
	ShowQueue1(&q);
	for (int i = 25; i < 57; i++)
	{
		Enqueue(i, &q);
	}
	ShowQueue1(&q);
	Destroy1(&q);
}