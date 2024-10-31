#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

//int num;
	//scanf("%d", &num);
	//printf("%d", num);
	// ㄱ 을 입력하면 ㄱ(3바이트) 이 차지하는 바이트내용이 저장되고 인트형식으로 출력된다.

// 예제 1번
void Example1()
{
	int a; int b;
	scanf("%d %d", &a, &b);
	printf("a+b = %d a-b = %d", a + b, a - b);
}
void Example2()
{
	int a; int b; int c;
	scanf("%d %d %d", &a, &b, &c);
	printf("%dx%d+%d = %d", a, b, c, a * b + c);
}

void Example3()
{
	int a;
	scanf("%d", &a);
	printf("%d의제곱 = %d", a, a * a);
}

void Example4()
{
	int a; int b; 
	scanf("%d %d", &a, &b);
	if (b == 0)
		printf("나눌 수 없습니다.");
	else
		printf("몫과 나머지: %d, %d", a / b, a % b);
}

void Example5()
{
	int num1, num2, num3 = 0;
	scanf("%d %d %d", &num1, &num2, &num3);
	if (num1 == 0)
	{
		printf("나눌 수 없습니다.");
		return;
	}
	printf("결과: %d", (num1 - num2) * (num2 + num3) * (num3 % num1));
}