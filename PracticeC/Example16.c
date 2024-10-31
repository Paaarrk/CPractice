#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void Example16_00()
{
	/*
	arr[00][01][02][03][10][11][12][13]
	*/
	printf("2차원 배열의 주소 할당\n");
	int arr[2][4] = { 0 };
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("arr[%d][%d] : %lld\n", i, j, &arr[i][j]);
	}
	/*
	arr2[000][001][002][003][010][011][012][013][020][021][022][023][100][101][102][103]...
	*/
	printf("3차원 배열의 주소 할당\n");
	int arr2[2][3][4] = { 0 };
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 4; k++)
				printf("arr2[%d][%d][%d] : %lld\n", i, j, k, &arr2[i][j][k]);
		}
	}

	// 뒤를 선기준으로 생성된다. (일명 가로)
}

void Example16_01()
{
	int arr[3][9] = { 0 };
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 9; j++)
			arr[i][j] = (i + 1) * (j + 1);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
			printf("%d, ", arr[i][j]);
		printf("\n");
	}
}

void Example16_02()
{
	int arr[2][4] = { 1,2,3,4, 5,6,7,8 };
	int arr2[4][2];

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++)
			arr2[j][i] = arr[i][j];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
			printf("arr[%d][%d] : %d ", i, j, arr2[i][j]);
		printf("\n");
	}
}

void Example16_03()
{
	int hangul = 0, english = 0, math = 0, history = 0;
	int pSum = 0, sSum = 0, fSum = 0;	// 사람의 총점, 과목의 총점, 전체 총합
	int arr[5][5];
	for (int i = 0; i < 4; i++)
	{
		scanf("%d %d %d %d", &hangul, &english, &math, &history);
		arr[i][0] = hangul;
		arr[i][1] = english;
		arr[i][2] = math;
		arr[i][3] = history;
	}

	// 합 구하기
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			pSum += arr[i][j];
			sSum += arr[j][i];
		}
		arr[i][4] = pSum;
		arr[4][i] = sSum;
		fSum += pSum;
		pSum = 0; sSum = 0;
	}
	arr[4][4] = fSum;

	// 검증 출력
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
	
}


