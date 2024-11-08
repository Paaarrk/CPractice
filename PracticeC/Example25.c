#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"

void Example25_00()
{
	int c;
	char* str;
	scanf("%d", &c);
	getchar();
	str = (char *)malloc(sizeof(char)*(c + 1));
	fgets(str, c + 1, stdin);
	str[strlen(str) - 1] = 0;

	int len = strlen(str);
	int bef = len - 1;
	for (int i = len - 1; i >= 0; i--)
	{
		if (str[i] == ' ')
		{
			for (int j = i + 1; j <= bef; j++)
			{
				fputc(str[j], stdout);
			}
			fputc(' ', stdout);
			bef = i - 1;
		}
		else if (i == 0)
		{
			for (int j = i; j <= bef; j++)
				fputc(str[j], stdout);
			fputc(' ', stdout);
		}
	}
	

}

void Example25_01()
{
	int count = 0;
	int size = 5;
	int input = 0;
	int* arr = (int*)malloc(sizeof(int) * size);

	while (1)
	{
		scanf("%d", &input);
		if (input == -1)
			break;
		if (count == size)
		{
			size += 3;
			arr = (int*)realloc(arr, sizeof(int) * size);
		}
		arr[count] = input;
		count++;
	}

	for (int i = 0; i < count; i++)
		printf("%d ", arr[i]);
}