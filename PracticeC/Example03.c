#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

//int num;
	//scanf("%d", &num);
	//printf("%d", num);
	// �� �� �Է��ϸ� ��(3����Ʈ) �� �����ϴ� ����Ʈ������ ����ǰ� ��Ʈ�������� ��µȴ�.

// ���� 1��
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
	printf("%d������ = %d", a, a * a);
}

void Example4()
{
	int a; int b; 
	scanf("%d %d", &a, &b);
	if (b == 0)
		printf("���� �� �����ϴ�.");
	else
		printf("��� ������: %d, %d", a / b, a % b);
}

void Example5()
{
	int num1, num2, num3 = 0;
	scanf("%d %d %d", &num1, &num2, &num3);
	if (num1 == 0)
	{
		printf("���� �� �����ϴ�.");
		return;
	}
	printf("���: %d", (num1 - num2) * (num2 + num3) * (num3 % num1));
}