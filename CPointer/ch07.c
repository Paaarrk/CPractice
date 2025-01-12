#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
/*
** 포인터와 구조체 **
* My Result *
1)	연산자 우선 순위 : . ->	[] > & *

1.	구조체의 주소 저장하기
 
2.	다차원 포인터, 배열, 구조체

3.	구조체 멤버로 주소 저장하기

4.	자신의 주소를 저장하는 구조체

*/

void wbcs()
{
	char str[] = "ABC한글";
	int size = sizeof(str);
	int len = strlen(str);
	printf("%d, %d", size, len);
}