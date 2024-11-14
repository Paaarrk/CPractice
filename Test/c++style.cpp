#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "c++style.h"
#include "list0.h"
#include "Point.h"
#include "BubbleSort.h"
using std::cout;
using std::endl;


void CPlusStyle0()
{
	srand(time(NULL));
	DoublyLinkedList0<int> list;
	list.ShowList();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			int num = 10 * i + j;
			list.PushFront(num);
		}
	}
	list.ShowList();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			int num = 10 * i + j;
			list.PushRear(num);
		}
	}
	list.ShowList();

	for (int i = 0; i < 100; i++)
	{
		list.Delete((rand() % 250));
	}
	list.ShowList();

	DoublyLinkedList0<double> list2;
	list2.ShowList();
	double num1 = 1.2;
	double num2 = 4.67;
	double num3 = 245.243;
	list2.PushFront(num1);
	list2.ShowList();
	list2.PushRear(num2);
	list2.ShowList();
	list2.Delete(1);
	list2.ShowList();
	list2.PushRear(num3);
	list2.ShowList();


}
void CPlusStyle0Point()
{
	srand(time(NULL));
	DoublyLinkedList0<Point> list;
	const char* name = "Point¿‘¥œ¥Ÿ";
	Point* p;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			list.PushFront(*(new Point(10 * i, 10 * j, name)));
		}
	}
	list.ShowList();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			list.PushRear(*(new Point(i, j, name)));
		}
	}
	list.ShowList();
	for (int i = 0; i < 3; i++)
	{
		list.Delete((rand() % 250));
	}
	list.ShowList();
}
void BubbleSort()
{
	srand(time(NULL));
	int arr[100];
	for (int i = 0; i < 100; i++)
	{
		arr[i] = (rand() % 200);
	}
	DesSort<int> des;
	AscSort<int> asc;

	Sort<int>(arr, 100, des);
	for (int i = 0; i < 100; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
	Sort<int>(arr, 100, asc);
	for (int i = 0; i < 100; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
}