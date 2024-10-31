#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

int* SquareByReference(int* num)
{
	(*num) *= (*num);
	return num;
}

int SquareByValue(int num)
{
	return num * num;
}

void Swap3(int*, int*, int*);
void Example14_00()
{

}

void Example14_01()
{
	int num = 0;
	scanf("%d", &num);

	printf("%d, %d", *SquareByReference(&num), SquareByValue(num));
	// 버퍼의 계산순서는 뒤에부터이다. (<- 방향)
}

void Example14_02()
{
	int n1 = 1, n2 = 2, n3 = 3;
	Swap3(&n1, &n2, &n3);
	printf("%d, %d, %d", n1, n2, n3);
}


//함수 정의
void Swap3(int* n1, int* n2, int* n3)
{
	int temp = *n2;
	*n2 = *n3;
	*n3 = *n1;
	*n1 = temp;
}