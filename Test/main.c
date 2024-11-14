#define _CRT_SECURE_NO_WARNINGS
//#include "c++style.h"
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
#include "cstyle.h"

//void quickSort(int*, int, int);
//int partition(int*, int, int);
//bool check(int*, int);

int main(void)
{
	//CPlusStyle0();
	//CPlusStyle0Point();
	//CStyle0();
	//BubbleSort();
	CStyle1();


	//bool t;
	//while (true)
	//{
	//	srand(time(NULL));
	//	int arr[1000];
	//	for (int i = 0; i < 1000; i++)
	//	{
	//		arr[i] = (rand() % 1000);
	//	}
	//	quickSort(arr, 0, 999);
	//	//for (int i = 0; i < 100; i++)
	//	//{
	//	//	printf("%d ", arr[i]);
	//	//}
	//	t = check(arr, 1000);
	//	std::cout << t << ' ';
	//}
	return 0;
}

//int partition(int* arr, int p, int q)
//{
//	int pv = arr[p];
//	int l = p + 1;
//	int h = q;
//	int temp = 0;
//	while (true)
//	{
//		while (arr[l] < pv)
//		{
//			l++;
//		}
//		while (arr[h] > pv)
//		{
//			h--;
//		}
//
//		if (l < h)
//		{
//			temp = arr[l];
//			arr[l] = arr[h];
//			arr[h] = temp;
//			l++; h--;
//		}
//		else
//		{
//			temp = arr[h];
//			arr[h] = pv;
//			arr[p] = temp;
//			return h;
//		}
//	}
//}
//
//void quickSort(int* arr, int p, int q)
//{
//	int pv = 0;
//	if (p < q)
//	{
//		pv = partition(arr, p, q);
//		quickSort(arr, p, pv - 1);
//		quickSort(arr, pv + 1, q);
//	}
//}
//
//bool check(int* arr, int len)
//{
//	for (int i = 0; i < len - 1; i++)
//	{
//		if (arr[i] > arr[i + 1])
//			return false;
//		else
//			continue;
//	}
//	return true;
//}