#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void Example12_00() {
	//포인터의 사이즈 (64비트)
	int num = 11;
	int* ptr = &num;
	printf("%d, %d", sizeof(ptr), sizeof(&num));
}

/*
0x0000(num) [00][00][00][0A]
ptr1[][][][][][][][0x0000]
ptr2[][][][][][][][0x0000]
*ptr1 = 0x0000  주소를 찾아간 값 0000000A를 읽음
*ptr2 = 0x0000  주소를 찾아간 값 0000000A를 읽음
*/

void Example12_02()
{
	int num1 = 10, num2 = 20;
	int *ptr1, *ptr2;
	ptr1 = &num1;
	ptr2 = &num2;
	(*ptr1) += 10;
	(*ptr2) -= 10;
	printf("ptr1 주소: %d, ptr2 주소: %d\n", ptr1, ptr2);
	//*ptr1 = num2;	//값을 바꾸는것(주소에 저장된 값)
	//*ptr2 = num1;	//값을 바꾸는것(주소에 저장된 값)
	//printf("ptr1 주소: %d, ptr2 주소: %d", ptr1, ptr2);
	ptr1 = &num2;
	ptr2 = &num1;

	printf("ptr1 주소: %d, ptr2 주소: %d\n, ptr1 값: %d, ptr2 값: %d", ptr1, ptr2, *ptr1, *ptr2);
}