#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void Example8_01()
{
	const int MAX = 100;
	for (int i = 1; i < MAX; i++)
	{
		if (i % 7 == 0 || i % 9 == 0)
			printf("7의배수와 9의 배수: %d\n", i);
	}
}

void Example8_02()
{
	int num1, num2;
	printf("두 수 입력: ");
	scanf("%d %d", &num1, &num2);
	printf("두 수의 차 절댓 값: ");
	if (num1 > num2)
		printf("%d\n", num1 - num2);
	else
		printf("%d\n", num2 - num1);
}

void Example8_03()
{
	int sc1, sc2, sc3;
	printf("학생의 점수 입력: 국, 영, 수: ");
	scanf("%d %d %d", &sc1, &sc2, &sc3);
	printf("학생의 평균, 등급: ");
	double avg = ((double)sc1 + sc2 + sc3) / 3;
	if (avg > 90)
		printf("%f, A등급", avg);
	else if (avg > 80)
		printf("%f, B등급", avg);
	else if (avg > 70)
		printf("%f, C등급", avg);
	else if (avg > 50)
		printf("%f, D등급", avg);
	else
		printf("%f, F등급", avg);
}

void Example8_04()
{
	int num1, num2, result;
	printf("두 수 입력: ");
	scanf("%d %d", &num1, &num2);
	printf("두 수의 차 절댓 값: ");
	result = num1 > num2 ? num1 - num2 : num2 - num1;
	printf("%d\n", result);
}

void Example8_05()
{
	for (int i = 1; i < 9; i++)
	{
		if (i % 2 != 0)
			continue;
		printf("%d단!\n", i);
		for (int j = 1; j <= 9; j++)
		{
			if (j > i)
				break;
			printf("%d x %d = %d\n", i, j, i * j);
		}
	}
}

void Example8_06()
{
	for (int A = 1; A <= 9; A++)
	{
		for (int Z = 1; Z <= 9; Z++)
		{
			if (A == Z)
				continue;

			if (10 * A + Z + 10 * Z + A == 99)
				printf("A: %d, Z: %d\n", A, Z);
		}
	}
}

void Example8_07()
{
	int n;
	scanf("%d", &n);
	switch (n / 10)
	{
	case 0:
		printf("0이상 10 미만");
		break;
	case 1:
		printf("10이상 20 미만");
		break;
	case 2:
		printf("20이상 30 미만");
		break;
	case 3:
		printf("30이상 40 미만");
		break;
	default:
		printf("40 이상!");
	}
}

void Example8_08()
{
	// goto 문의 연습
	int sum = 0;
	int num = 0;
ONE:
	scanf("%d", &num);
	if (num == 0)
		goto TWO;
	sum += num;
	goto ONE;
TWO:
	printf("입력된 수의 총 합: %d\n", sum);
}