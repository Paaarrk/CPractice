#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void Ch02_01()
{
	int n = 0x101010;
	int** npp = &n;
	//int* p = &n;
	//npp = &p;
	
	printf("%8X %8X", n, *npp);
	//**npp 는 읽을 수 없다. 뭔짓을 해도 불가능하다. -1차원으로 가기 때문이다. (n이 0차원 기준)
}

void Ch02_02()
{
	// 다차원 포인터
	int n = 0x20;
	int* np = &n;
	int** npp = &np;

	/*
	--- STACK ---
	[][][][] - &n
	[][][][][][][][] - &np = &n + 24
	[][][][][][][][] - &npp = &np + 20
	*/

	printf("%X %X %X \n", n, *np, **npp);
	printf("%llX %llX %llX \n", &n, np, *npp);
	printf("%llX %llX \n", &np, npp);
	printf("%llX \n", &npp);
	printf("SIZEOF: %X %X %X \n", sizeof(n), sizeof(*np), sizeof(**npp));
	printf("SIZEOF: %X %X %X \n", sizeof(&n), sizeof(np), sizeof(*npp));
	printf("SIZEOF: %X %X \n", sizeof(&np), sizeof(npp));
	printf("SIZEOF: %X \n", sizeof(&npp));
	printf("%llX %llX %llX \n", &n + 1, np + 1, *npp + 1);	//np가 가리키는 값이 4바이트 값이므로 주소가 4만큼 증가
	printf("%llX %llX \n", &np + 1, npp + 1);
	printf("%llX \n", &npp + 1);
}

void Ch02_03()
{
	// 포인터로 장난치기
	long long n = 0x1122334455667788;
	printf("n의 주소:\t %llX, 값: \t%llX \n", &n, n);
	int* niptr = &n;
	printf("niptr의 주소:\t %llX, 값: \t%X \n", &niptr, niptr);
	int* niptrup = (int*)& n + 1;
	printf("niptrup의 주소:\t %llX, 값: \t%X \n", &niptrup, niptrup);
	printf("n을 출력하기(다른 방법) %X%X \n", *niptrup, *niptr);


	int n2 = 0x12345678;
	printf("%llX, %llX", &n2, &n2 + 1); //한차원 낮춘 sizeof를 계산해서 1에 곱해 더한다.
}