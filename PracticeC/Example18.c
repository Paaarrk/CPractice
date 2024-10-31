#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void PrintArr(int(*arr)[3][4], int);

void Example18_00()
{
	int arr[2][3][4] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };
	printf("sizeof arr[0]: %d\n", sizeof(arr[0]));
	PrintArr(arr, sizeof(arr) / sizeof(arr[0]));
}

void PrintArr(int(*arr)[3][4], int len)
{
	printf("{");
	for (int i = 0; i < len; i++)
	{
		printf("{ ");
		for (int j = 0; j < 3; j++)
		{
			printf("{ ");
			for (int k = 0; k < 4; k++)
			{
				printf("%d ", (*(arr[i][j] + k)));
			}
			printf(" }");
		}
		printf(" }");
	}
	printf(" }");
}