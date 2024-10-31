/* Bubble Sort */
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void Swap(int* t1, int* t2);

void DesSort(int* arr, int len);




void Example15_00()
{
	int arr[] = { 1, 4, 55, 3, 4352, 465, 54, 432, 4, 64, 543 };

	DesSort(arr, sizeof(arr) / sizeof(int));
}

// 함수 정의
void Swap(int* t1, int* t2)
{
	if (*t1 < *t2)
	{
		int temp = *t1;
		*t1 = *t2;
		*t2 = temp;
	}
}

void DesSort(int* arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			Swap(&arr[j], &arr[j + 1]);
		}
	}

	for (int i = 0; i < len; i++)
		printf("%d ", arr[i]);
}