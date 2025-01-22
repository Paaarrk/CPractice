#include <stdio.h>


void Ch9_01(void)
{
	int** npp;
	int* (*npp2);
	int a = 1;
	int* b = &a;
	npp = &b;
	npp2 = &b;

	printf_s("%d %d", **npp2, **npp);
}