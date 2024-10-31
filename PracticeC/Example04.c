#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

/* 
// 4-1
// 1) 10진수를 2진수와 16진수로
8 = 100, 8
9 = 101, 9
10 = 110, A
11 = 111, B
12 = 1100, C
13 = 1101, D
14 = 1110, E
15 = 1111, F
16 = 10000, 10
17 = 10001, 11
18 = 10010, 12
19 = 10011, 13
20 = 10100, 14

// 2)10진수를 8진수로
5 = 5
6 = 6
7 = 7
8 = 10
9 = 11
10 = 12
11 = 13
12 = 14
13 = 15
14 = 16
15 = 17

// 4-2
// 1) 
2비트 표현가능 수 : 2^2 = 4
4비트 표현가능 수 : 2^4 = 16
1바이트(8비트) 표현가능 수 : 2^8 = 256
4바이트(32비트) 표현가능 수 : 2^32 = 4,294,967,296

// 2)
1, 2, 4, 8, 16, 32, 64, 128

// 3)
17, 162, 247

// 4-3
1. 79, 69
2. 169, 240(15*2^4 - shift 연산)
*/

void Example4_0() {
	int num = -16;
	printf("2칸 오른쪽 이동 결과: %d\n", num >> 2);
	printf("3칸 오른쪽 이동 결과: %d\n", num >> 3);
	printf("num 은 변하지 않음 %d\n", num);
}
void Example4_1() {
	int num1; int num2;
	scanf("%d %d", &num1, &num2);
	num1 = ~num1; num2 = ~num2;
	num1 += 1; num2 += 1;
	printf("%d %d\n", num1, num2);
}

void Example4_2()
{
	int num = 3;
	num = num << 3 >> 2;
	printf("%d", num);
}
