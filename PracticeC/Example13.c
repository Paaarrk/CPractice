#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void Example13_00()
{
	char str[] = "MyConst";
	char* str2 = str;

	str[2] = 'c';
	str2[2] = 'C'; //배열로 선언된 str의 주소를 받아서 (배열 형태로 인정됨) 가능함 -> 이것은 함수의 매개변수에서도 적용된다.
	printf("%s %s", str, str2);

	char* str3 = "MyStatic";
	// str3[2] = 's'; 불가능!
	printf(" %s", str3);
}

void Example13_01()
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	int* ptr = arr;
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		*(ptr++) += 2;
	}
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
		printf("%d, ", *(arr+i));
} 

void Example13_02()
{
	int sum = 0;
	int arr[5] = { 1, 2, 3, 4, 5 };
	int* ptr = &arr[4];
	for (int i = 0; i < 5; i++)
	{
		sum += *(ptr--);
	}
	printf("%d", sum);
}

void Example13_03()
{
	int arr[6] = { 1, 2, 3, 4, 5, 6 };
	int* ptrb = arr;
	int* ptre = arr + 5;
	int temp = 0;
	for (int i = 0; i < 3; i++)
	{
		temp = *ptrb;
		*ptrb = *ptre;
		*ptre = temp;
		++ptrb; --ptre;
	}
	for (int i = 0; i < 6; i++)
		printf("%d, ", *(arr + i));
}

void Example13_04()
{
	/*
	arr -> [int num1][int num2][int num3]
	            ㄴ_______ㅣ________ㅣ________ num1
				          ㄴ_______ㅣ________ num2
						            ㄴ_______ num3
	*/

	int num1 = 10, num2 = 20, num3 = 30;
	int* arr[3] = {&num1, &num2, &num3};
	for (int i = 0; i < sizeof(arr) / sizeof(double); i++)
	{
		printf("%ld의 값: %d\n", *(arr + i), **(arr + i));
	}
}

void Example13_05()
{
	/*   0x00                                                0x12    
	str -> [C][a][n][ ][I][ ][C][h][a][n][g][e][?][ ][Y][e][s][\0]
	*/
	char* str1 = "Can I Change? Yes";	//주소가 저장되서 8바이트
	char str2[] = "Can I Change? Yes";	//문자열 자체가 배열에 저장되서 18바이트

	printf("%d, %d\n", sizeof(str1), sizeof(str2));

	
	//상수형 문자열이여서 값을 읽을 수는 있지만, 바꿀 수는 없다.
	for (int i = 0; i < 18; i++)
	{
		printf("%ld, %c\n", str1 + i, *(str1 + i));
	}

}