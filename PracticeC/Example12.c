#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void Example12_00() {
	//�������� ������ (64��Ʈ)
	int num = 11;
	int* ptr = &num;
	printf("%d, %d", sizeof(ptr), sizeof(&num));
}

/*
0x0000(num) [00][00][00][0A]
ptr1[][][][][][][][0x0000]
ptr2[][][][][][][][0x0000]
*ptr1 = 0x0000  �ּҸ� ã�ư� �� 0000000A�� ����
*ptr2 = 0x0000  �ּҸ� ã�ư� �� 0000000A�� ����
*/

void Example12_02()
{
	int num1 = 10, num2 = 20;
	int *ptr1, *ptr2;
	ptr1 = &num1;
	ptr2 = &num2;
	(*ptr1) += 10;
	(*ptr2) -= 10;
	printf("ptr1 �ּ�: %d, ptr2 �ּ�: %d\n", ptr1, ptr2);
	//*ptr1 = num2;	//���� �ٲٴ°�(�ּҿ� ����� ��)
	//*ptr2 = num1;	//���� �ٲٴ°�(�ּҿ� ����� ��)
	//printf("ptr1 �ּ�: %d, ptr2 �ּ�: %d", ptr1, ptr2);
	ptr1 = &num2;
	ptr2 = &num1;

	printf("ptr1 �ּ�: %d, ptr2 �ּ�: %d\n, ptr1 ��: %d, ptr2 ��: %d", ptr1, ptr2, *ptr1, *ptr2);
}