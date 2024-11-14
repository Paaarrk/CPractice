#define _CRT_SECURE_NO_WARNINGS
#include "cqueue.h"
#include "bublesort.h"
#include "list.h"
#include "Point.h"
//#include <stdio.h>
//#include <time.h>
//#include <stdlib.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

static bool check(int* arr, int len, bool des)
{
	if (des)
	{
		for (int i = 0; i < len - 1; i++)
		{
			if (arr[i] < arr[i + 1])
				return false;
		}
	}
	else {
		for (int i = 0; i < len - 1; i++)
		{
			if (arr[i] > arr[i + 1])
				return false;
		}
	}
	return true;
}
static void QueueT()
{
	Queue1 q;
	InitQueue1(&q);

	for (int i = 0; i < 100; i++)
	{
		Enqueue1(i, &q);
	}
	ShowQueue1(&q);
	for (int i = 0; i < 68; i++)
	{
		printf("%d \n", Dequeue1(&q));
	}
	ShowQueue1(&q);
	for (int i = 25; i < 347; i++)
	{
		Enqueue1(i, &q);
	}
	ShowQueue1(&q);
	Destroy1(&q);
}
static void BubbleT()
{
	using namespace std;
	int count = 0;
	int arr[1000];
	
	while (count < 1000)
	{
		for (int i = 0; i < 1000; i++)
		{
			arr[i] = (rand() % 2000);
		}
		Des<int> descent;
		Asc<int> ascent;
		bsort<int>(arr, 1000, descent);
		cout << check(arr, 1000, true);
		bsort<int>(arr, 1000, ascent);
		cout << check(arr, 1000, false);
		count++;
	}
	
}
static void ListT()
{
	List<Point> list;
	int count = 0;
	while (count < 50)
	{
		list.PushFront(*(new Point(rand() % 10, rand() % 10)));
		list.ShowInfo();
		count++;
	}
	while (count > 0)
	{
		list.PushRear(*(new Point(rand() % 10, rand() % 10)));
		list.ShowInfo();
		count--;
	}


	while (list.GetCount() != 0)
	{
		Point p(list.Delete(*(new Point(rand() % 10, rand() % 10))));
		cout << p << endl;
		list.ShowInfo();
	}
}

int main(void)
{
	srand(time(NULL));
	//QueueT();
	//BubbleT();
	ListT();
	return 0;
}