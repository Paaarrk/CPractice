#include <cstdlib>
#include <ctime>
#include "list.h"
#include "point.h"

static void TestList()
{
	List<Point> list;
	int count = 0;

	while (count < 10)
	{
		list.PushFront(*(new Point(rand() % 10, rand() % 10)));
		list.Info();
		++count;
	}
	while (count > 0)
	{
		list.PushRear(*(new Point(rand() % 10, rand() % 10)));
		list.Info();
		--count;
	}
	while (list.GetCount() != 0)
	{
		cout << list.Delete(*(new Point(rand() % 10, rand() % 10)));
		list.Info();
	}
}

static void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
static void bubble(int* arr, int len, bool des)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (des)
			{
				if (arr[j] < arr[j + 1])
				{
					swap(arr[j], arr[j + 1]);
				}
			}
			else
			{
				if (arr[j] > arr[j + 1])
				{
					swap(arr[j], arr[j + 1]);
				}
			}
		}
	}
}
static bool checksort(int* arr, int len, bool des)
{
	for (int i = 0; i < len - 1; i++)
	{
		if (des)
		{
			if (arr[i] < arr[i + 1])
				return false;
		}
		else {
			if (arr[i] > arr[i + 1])
				return false;
		}
	}
	return true;
}
static void TestBubble()
{
	int count = 0;
	int arr[1000];
	while (count < 100)
	{
		for (int i = 0; i < 1000; i++)
		{
			arr[i] = rand() % 2000;
		}
		bubble(arr, 1000, true);
		cout << checksort(arr, 1000, true);
		bubble(arr, 1000, false);
		cout << checksort(arr, 1000, false);
		count++;
	}
}


int main()
{
	srand(time(NULL));
	//TestList();
	TestBubble();
	return 0;
}