#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void Example7_01()
{
	int num,i = 1,result = 1;
	scanf("%d", &num);

	printf("���丮�� ���(while): ");
	while (i <= num)
	{
		result *= i;
		i++;
	}
	printf("��� %d\n", result);
	i = 0; result = 1;
	printf("���丮�� ���(do-while): ");
	do {
		i++;
		result *= i;
	} while (i < num);
	printf("��� %d\n", result);
	i = 1; result = 1;
	printf("���丮�� ���(for): ");
	for (i = num; i > 0; i--)
	{
		result *= i;
	}
	printf("��� %d\n", result);
}