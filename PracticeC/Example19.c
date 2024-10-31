#define _CRT_NO_SECURE_WARNINGS
#include "stdio.h"

int Max(int(*arr)[2], int len);
int Min(int(*arr)[2], int len);
void PrintMaxAndMin(int(*arr)[2], int len, int (*max)(int(*)[2], int), int (*min)(int(*)[2], int));

void Example19_00()
{
	printf("함수 포인터 연습\n");
	int arr[7][2] = { 3,45,6,5,45,3456,6574,567,73,73,6543,56,56,65 };
	int arr2[2][2] = { 4,1,3,4 };

	int (*fptr)(int(*)[2], int) = PrintMaxAndMin;
	fptr(arr, sizeof(arr) / sizeof(arr[0]), Max, Min);
	fptr(arr2, sizeof(arr2) / sizeof(arr2[0]), Min, Max);

	printf("void 포인터 연습\n");
	void* ptr1 = Max;
	void* ptr2 = Min;
	void* ptr3 = arr;
	printf("void포인터 Max: %lld, Min: %lld, arr: %lld\n", ptr1, ptr2, ptr3);
	// void포인터는 주소 저장만 가능하다.

	// ptr1(arr, sizeof(arr) / sizeof(arr[0])); : 형식이 없어서 오류남.
	int (*fptr2)(int(*)[2], int) = ptr1; // void포인터의 주소를 넣음, Max의 주소
	printf("%d\n", fptr2(arr, sizeof(arr) / sizeof(arr[0])));	// 실행 된다.
}

int Max(int(*arr)[2], int len)
{
	int max = 0;
	for(int i = 0; i < len; i++)
		for (int j = 0; j < 2; j++)
		{
			if (max < arr[i][j])
				max = arr[i][j];
		}

	return max;
}

int Min(int(*arr)[2], int len)
{
	int min = 99999;
	for(int i = 0; i < len; i++)
		for (int j = 0; j < 2; j++)
		{
			if (min > arr[i][j])
				min = arr[i][j];
		}

	return min;
}

void PrintMaxAndMin(int(*arr)[2], int len, int (*max)(int(*)[2], int), int (*min)(int(*)[2], int))
{
	printf("최대: %d, 최소: %d\n", max(arr, len), min(arr, len));
}