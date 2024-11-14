#include <cstdlib>
#include <ctime>
#include "list.h"
#include "point.h"

static void TestList()
{
	int count = 0;
	list<Point> list;
	while (count < 50)
	{
		list.pushfront(*(new Point(rand() % 10, rand() % 10)));
		list.showlist();
		count++;
	}
	while (count > 0)
	{
		list.pushrear(*(new Point(rand() % 10, rand() % 10)));
		list.showlist();
		count--;
	}

	while (list.getcount() != 0)
	{
		list.del(*(new Point(rand() % 10, rand() % 10)));
		list.showlist();
	}
}

static void bubblesort(int* arr, int len, bool des)
{
	int temp = 0;
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (des)
			{	//desce
				if (arr[j] < arr[j + 1])
				{
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
			else
			{	//asce
				if (arr[j] > arr[j + 1])
				{
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
	}
}
static bool sortcheck(int* arr, int len, bool des)
{
	for (int i = 0; i < len - 1; i++)
	{
		if (des)
		{
			if (arr[i] < arr[i + 1])
				return false;
		}
		else
		{
			if (arr[i] > arr[i + 1])
				return false;
		}
	}
	return true;
}
static void TestSort()
{
	int count = 0;
	int arr[1000];
	while (count < 1000)
	{
		for (int i = 0; i < 1000; i++)
		{
			arr[i] = rand() % 1000;
		}
		bubblesort(arr, 1000, true);
		cout << sortcheck(arr, 1000, true);
		bubblesort(arr, 1000, false);
		cout << sortcheck(arr, 1000, false);
		count++;
	}

}
int main(void)
{
	srand(time(NULL));
	TestSort();
	//TestList();
	return 0;
}