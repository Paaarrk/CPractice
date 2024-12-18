#define _CRT_SECURE_NO_WARININGS

#include <stdio.h>

/*
배열과 포인터
1.	배열과 포인터의 차이 : sizeof()연산자
	포인터변수 cp에 대해 cp[n] = cp + n(sizeof(*cp))

2.	1차원 배열을 1차원 포인터로

3.	1차원 배열을 n차원 포인터로	
	* 보다 []연산자가 우선순위가 높다!!
4.	n차원 배열을 1차원 포인터로

5.	n차원 배열을 m차원 포인터로

6.	배열과 다른 크기의 포인터로 배열을 읽어보기

7.	단일 변수를 활용해 포인터로 계산해보기 (주소 확인차 인데 5번에서 함)


		**My Result**
		1.	모든 n차원 배열은 1차원으로 생각하고 포인터 연산을 하면 편하다.
			예)	a[2][3][4] = b[24]
				a + n = b + 12*n
				*(a + n) + m = b + 12*n + 4*m
				*(*(a + n) + m) + k = b + 12*n + 4*m + k
		2.	그렇다 보니 배열을 벗어나는 연산도 실제로는 가능하다.
			예)	a[4][2]
				a[3][0] == *(*(a+2) + 2) [== **(a + 6)]

*/

void Ch04_01()
{
	char c = 0x41;
	char(*cp) = &c;
	int i = 0x112233344;
	int(*ip) = &i;

	printf("주소 값 비교 \n %llX = %llX \n %llX = %llX \n\n", (long) & c, (long)cp, (long)&i, (long)ip);
	printf("값 비교 \n %X = %X \n %X = %X \n\n", c, *cp, i, *ip);
	printf("주소의 크기 : %X, %X \n", (int)sizeof(cp), (int)sizeof(ip));
}

void Ch04_02()
{
	short arr[6] = { 0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666 };
	short* p = arr + 3;	// 같은 타입이라 형변환 필요 없음
	
	printf("sizeof() result \n %d == 12 \n %d == 8 \n\n", (int)sizeof(arr), (int)sizeof(p));
	printf("값으로 비교 \n %X == %X == %X \n %X == %X == %X \n %X == %X == %X \n %X == %X == %X \n %X == %X == %X \n %X == %X == %X \n\n",
		*(arr + 0), p[-3], (p - 3)[0], 
		*(arr + 1), p[-2], (p - 2)[0], 
		*(arr + 2), p[-1], (p - 1)[0], 
		*(arr + 3), p[0], (p - 0)[0], 
		*(arr + 4), p[1], (p + 1)[0], 
		*(arr + 5), p[2], (p + 2)[0]);
}

void Ch04_03()
{
	short arr[6] = { 0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666 };
	short(*p1)[2] = (short(*)[2])arr;	// 형 변환
	short(*p2)[3] = (short(*)[3])arr + 1;	// 형 변환

	printf("sizeof() result \n %d == 12 \n %d == 8 \n %d == 8 \n\n", (int)sizeof(arr), (int)sizeof(p1), (int)sizeof(p2));
	printf("-- p1을 사용해서 읽기 -- \n");
	printf("%X == %X == %X \n%X == %X == %X \n%X == %X == %X \n%X == %X == %X \n%X == %X == %X \n%X == %X == %X \n\n",
		*(arr + 0), p1[0][0], (*(p1 + 0))[0],
		*(arr + 1), p1[0][1], (*(p1 + 0))[1],
		*(arr + 2), p1[1][0], (*(p1 + 1))[0],
		*(arr + 3), p1[1][1], (*(p1 + 1))[1],
		*(arr + 4), p1[2][0], (*(p1 + 2))[0],
		*(arr + 5), p1[2][1], *(p1[2] + 1));
	printf("-- p2을 사용해서 읽기 -- \n");
	printf("%X == %X == %X \n%X == %X == %X \n%X == %X == %X \n%X == %X == %X \n%X == %X == %X \n%X == %X == %X \n\n",
		*(arr + 0), p2[-1][0], (*(p2 - 1))[0],
		*(arr + 1), p2[-1][1], (*(p2 - 1))[1],
		*(arr + 2), p2[-1][2], (*(p2 - 1))[2],
		*(arr + 3), p2[0][0], (*(p2 + 0))[0],
		*(arr + 4), p2[0][1], (*(p2 + 0))[1],
		*(arr + 5), p2[0][2], *(p2[0] + 2));

}

void Ch04_04()
{
	int arr[2][3][2] = { {{0x1111, 0x2222}, {0x3333,0x4444}, {0x5555,0x6666}}, {{0x7777,0x8888}, {0x9999,0xaaaa}, {0xbbbb,0xcccc}} };
	int* p = (int*)(*(arr+1) + 2);	//　형 변환
	
	printf(" %X == %X \n %X == %X \n %X == %X \n %X == %X \n %X == %X \n %X == %X \n %X == %X \n %X == %X \n %X == %X \n %X == %X \n %X == %X \n %X == %X \n ",
		arr[0][0][0], (p - 10)[0],
		arr[0][0][1], (p - 10)[1],
		arr[0][1][0], (p - 10)[2],
		arr[0][1][1], (p - 10)[3],
		arr[0][2][0], (p - 10)[4],
		arr[0][2][1], (p - 10)[5],
		arr[1][0][0], (p - 10)[6],
		arr[1][0][1], (p - 10)[7],
		arr[1][1][0], (p - 10)[8],
		arr[1][1][1], (p - 10)[9],
		arr[1][2][0], (p - 10)[10],
		arr[1][2][1], (p - 10)[11]);
}

void Ch04_05()
{
	int arr[4][2] = { {0x11, 0x22}, {0x33, 0x44}, {0x55, 0x66}, {0x77, 0x88} };
	int(*p)[2][2] = (int(*)[2][2])(*(arr + 2) + 2);	// 형 변환 (arr + 2*2 + 2 = arr + 6)

	printf(" %X == %X \n %X == %X \n %X == %X \n %X == %X \n %X == %X \n %X == %X \n %X == %X \n %X == %X \n",
		arr[0][0], p[-1][-1][0],	//-6
		arr[0][1], p[-1][-1][1],	//-5
		arr[1][0], p[-1][0][0],	//-4
		arr[1][1], p[-1][0][1],		//-3
		arr[2][0], p[0][-1][0],		//-2
		arr[2][1], p[0][-1][1],		//-1
		arr[3][0], p[0][0][0],		//0
		arr[3][1], p[0][0][1]);		//+1
}

void Ch04_06()
{
	int arr[1][2] = { 0x44434241, 0x48474645 };
	short* sp = arr;
	char* cp = arr;

	printf("int로 출력\n");
	for (int i = 0; i < 2; i++)
		printf("%X \n", *((*arr) + i));
	printf("\n");

	printf("short로 출력\n");
	for (int i = 0; i < 4; i++)
		printf("%X \n", *(sp + i));
	printf("\n");

	printf("char로 출력\n");
	for (int i = 0; i < 8; i++)
		printf("%c \n", *(cp + i));
	printf("\n");
}