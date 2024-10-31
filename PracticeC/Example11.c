#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void Example11_01()
{
	int sum = 0, min = 2147483647, max = -2147483647;
	int arr[5] = { 0 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		scanf("%d", &arr[i]);
	}
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		sum += arr[i];
		if (min > arr[i])
			min = arr[i];
		if (max < arr[i])
			max = arr[i];
	}
	printf("최대: %d, 최소: %d, 총 합: %d", max, min, sum);
}

void Example11_02()
{
	char string[] = { 'G','o','o','d',' ','t','i','m','e','\n' };
	for (int i = 0; i < sizeof(string); i++)
		printf("%c", string[i]);
}

void Example11_03()
{
	//scanf로 입력한 문자열의 출력길이
	char str[50];
	scanf("%s", str);
	printf("출력 길이: %d", printf("%s", str));
}

void Example11_04()
{
	char str[50]; int num = 0;
	scanf("%s", str);
	for (int i = 0; i < 50; i++)
	{
		if (str[i] == '\0')
		{
			num = i; 
			break;
		}
	}
	printf("문자열 길이: %d", num);
}
void Example11_05()
{
	char str[50]; int num = 0;
	scanf("%s", str);
	for (int i = 0; i < 50; i++)
	{
		if (str[i] == '\0')
		{
			num = i;
			break;
		}
	}

	for (int i = 0; i < num / 2; i++)
	{
		char temp = str[i];
		str[i] = str[num - 1 - i];
		str[num - 1 - i] = temp;
	}
	printf("%s\n", str);
}

void Example11_06()
{
	char str[50]; int num = 0;
	scanf("%s", str);
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (num < str[i])
			num = str[i];
	}
	printf("%c", num);
}