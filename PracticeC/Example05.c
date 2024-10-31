#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void Example5_00()
{
	char num1 = 1, num2 = 2, result1 = 0;
	short num3 = 300, num4 = 400, result2 = 0;
	printf("int�� ũ��: %d\n", sizeof(int));
	printf("long�� ũ��: %d\n", sizeof(long));
	printf("long long�� ũ��: %d\n", sizeof(long long));

	// �Ϲ������� CPU���� �����ϱ� ���� ���� int�̱� ������ ���� ������ int�� ����ȯ �� ����ȴ�. (���� ����)
	printf("num1, num2 �� ũ��: %d, %d\n", sizeof(num1), sizeof(num2));
	printf("num3, num4 �� ũ��: %d, %d\n", sizeof(num3), sizeof(num4));
	printf("�� ����� int�� ����ȯ �� ���Ǿ� ����� ��ȯ�ȴ�.\n");
	printf("num1 + num2�� ũ��: %d\n", sizeof(num1 + num2));
	printf("num3 + num4�� ũ��: %d\n", sizeof(num3 + num4));
	// result�� �տ��� ����� ������ ���� ���� int�� ��� �� ����� ����ȯ �� ����ȴ�.
	result1 = num1 + num2;
	result2 = num3 + num4;
	printf("result1, result2 �� ũ��: %d, %d\n", sizeof(result1), sizeof(result2));

	printf("float ũ��: %d\n",sizeof(float));
	printf("double ũ��: %d\n", sizeof(double));
	printf("long double ũ��: %d\n", sizeof(long double));	//���� 8�� double�� ����. 12����Ʈ�� ��쵵 �ִ�.

	unsigned char c1 = -1;
	signed char c2 = -2;
	char c3 = -3;
	printf("unsigned c1, signed c2, char c3: %d, %d, %d : ���� �����Ϸ��� char�� �⺻������ unsigned char�� ó������ �� �� �ִ�.\n", c1, c2, c3);

	char hangul = '��';
	printf("sizeof �ѱ�: %d, ����: %c\n : �ѱ��� 3����Ʈ�̱� ������ �߷������� ������.(char�� �ƽ�Ű�ڵ带 ����)", sizeof(hangul), hangul);
}

void Example5_01()
{
	int x1; int y1; int x2; int y2;
	printf("�»���� x, y ��ǥ: ");
	scanf("%d %d", &x1, &y1);
	printf("���ϴ��� x, y ��ǥ: ");
	scanf("%d %d", &x2, &y2);
	printf("�簢���� ����: %d\n", (x2 - x1) * (y1 - y2));
}
void Example5_02()
{
	double d1, d2;
	printf("�ΰ��� �Ǽ� �Է�: ");
	scanf("%lf %lf", &d1, &d2);
	printf("��: %f, ��: %f, ��: %f, ��: %f\n", d1 + d2, d1 * d2, d1 - d2, d1 / d2);
	printf("%d", sizeof(d1 + d2));
}

void Example5_03()
{
	char x = -3;
	printf("%c\n", x);
	/*
	�ƽ�Ű�ڵ��� ���� ������ 0 ~ 127
	���� �빮�ڴ� 65 ~ 90
	���� �ҹ��ڴ� 97 ~ 122
	(32 ����)
	*/
}
void Example5_04()
{
	// �̷��� �Է¹����� ū�ϳ���.
	//char y;
	//scanf("%d", &y);
	//printf("%c\n", y);
	int y;
	scanf("%d", &y);
	printf("%c\n", y);	// 1����Ʈ��ŭ �о ���ڷ� ��ȯ
	//[90]
	y = y >> 8;
	//[90][0]
	y += 122;
	//[90][122]
	printf("%c\n", y);	// ������ ���� �о����. [122] ���
}

void Example5_05()
{
	char c;
	scanf("%c", &c);
	printf("%d", c);
}