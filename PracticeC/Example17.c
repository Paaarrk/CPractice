#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void MaxAndMin(int** dptrm, int** dptrM, int* arr, int len)
{
	*dptrm = &arr[0];
	*dptrM = &arr[len - 1];
}

void Example17_00()
{

}

void Example17_01()
{
	int* maxPtr;
	int* minPtr;
	int arr[5] = { 0 };
	MaxAndMin(&minPtr, &maxPtr, arr, 5);

	printf("&arr[4]: %lld, maxPtr: %lld, &arr[0]: %lld, minPtr: %lld\n", &arr[4], maxPtr, &arr[0], minPtr);
}