#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h";

// 함수 선언
int* CompareMinMax(int, int, int);
double CeltoFah(double);
void Fib(int);
int AddToTotal(int);
int Pow2(int);

void Example9_00()
{
	int len0 = printf("ab");
	int len1 = printf("홍");
	int len2 = printf("길");
	int len3 = printf("동");
	int len4 = printf("a\b길동\n");
	int len5 = printf("홍\b길동\n");
	int len6 = printf("홍\b\b길동\n");
	printf("%d %d %d %d %d %d %d", len0, len1, len2, len3, len4, len5, len6);
	// CP949기준 한글은 2바이트이다.
}

void Example9_01()
{
	int x, y, z;
	scanf("%d %d %d", &x, &y, &z);
	int* arr = CompareMinMax(x, y, z);
	printf("최솟값: %d, 최댓값: %d", arr[0], arr[1]);
}

void Example9_02()
{
	double c;
	scanf("%lf", &c);
	c = CeltoFah(c);
	printf("화씨온도 %f", c);
}

void Example9_03()
{
	int n;
	scanf("%d", &n);
	Fib(n);
}

void Example9_04()
{
	int num, i;
	for (i = 0; i < 3; i++)
	{
		printf("입력%d: ", i + 1);
		scanf("%d", &num);
		printf("누적: %d \n", AddToTotal(num));
	}
}

void Example9_05()
{
	int n;
	scanf("%d", &n);
	printf("2의%d승 = %d", n, Pow2(n));
}

// 함수 정의
int* CompareMinMax(int x, int y, int z)
{
	int arr[2] = {0, 0};
	if (x > y)
	{
		if (x > z)
		{
			arr[1] = x;
			if (y > z)
			{
				arr[0] = z;
			}
			else
			{
				arr[0] = y;
			}
		}
		else
		{
			arr[1] = z;
			arr[0] = y;
		}
	}
	else
	{
		if (y >= z) 
		{
			arr[1] = y;
			if (z > x)
			{
				arr[0] = x;
			}
			else
			{
				arr[0] = z;
			}
		}
		else
		{
			arr[1] = z;
			arr[0] = x;
		}
	}
	return arr;
}
double CeltoFah(double c)
{
	c = c * 1.8 + 32.0;
	return c;
}
void Fib(int n) 
{
	int a0 = 0;
	int a1 = 1;
	if (n == 1)
	{
		printf("%d, ", a0);
	}
	else if (n == 2)
	{
		printf("%d, ", a0);
		printf("%d, ", a1);
	}
	else
	{
		printf("%d, ", a0);
		printf("%d, ", a1);
		int bef = a0;
		int af = a1;
		int res;
		for (int i = 2; i <= n; i++)
		{
			res = bef + af;
			printf("%d, ", res);
			bef = af;
			af = res;
		}
	}
}
int AddToTotal(int n)
{
	static int total;
	total += n;
	return total;
}
int Pow2(int n)
{
	if (n == 0)
		return 1;
	return 2 * Pow2(n - 1);
}