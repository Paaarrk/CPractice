#define _CRT_SECURE_NO_WARNINGS
#define SUM(A, B, C) ((A)+(B)+(C))
#define MUL(A, B, C) ((A)*(B)*(C))

#define PI 3.14
#define AREA(R) ((R)*(R)*PI)

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#include "stdio.h"
#include "stdlib.h"



void Example26_01()
{
	printf("%d \n", SUM(10, 11, 12));
	printf("%d", MUL(1, 2, 3));
}

void Example26_02()
{
	double rad = 3.0;
	printf("%lf", AREA(rad));
}

void Example26_03()
{
	printf("%d", MAX(44, 22));
}

