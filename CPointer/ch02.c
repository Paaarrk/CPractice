#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void Ch02_01()
{
	int n = 0x101010;
	int** npp = &n;
	//int* p = &n;
	//npp = &p;
	
	printf("%8X %8X", n, *npp);
	//**npp �� ���� �� ����. ������ �ص� �Ұ����ϴ�. -1�������� ���� �����̴�. (n�� 0���� ����)
}

void Ch02_02()
{
	// ������ ������
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
	printf("%llX %llX %llX \n", &n + 1, np + 1, *npp + 1);	//np�� ����Ű�� ���� 4����Ʈ ���̹Ƿ� �ּҰ� 4��ŭ ����
	printf("%llX %llX \n", &np + 1, npp + 1);
	printf("%llX \n", &npp + 1);
}

void Ch02_03()
{
	// �����ͷ� �峭ġ��
	long long n = 0x1122334455667788;
	printf("n�� �ּ�:\t %llX, ��: \t%llX \n", &n, n);
	int* niptr = &n;
	printf("niptr�� �ּ�:\t %llX, ��: \t%X \n", &niptr, niptr);
	int* niptrup = (int*)& n + 1;
	printf("niptrup�� �ּ�:\t %llX, ��: \t%X \n", &niptrup, niptrup);
	printf("n�� ����ϱ�(�ٸ� ���) %X%X \n", *niptrup, *niptr);


	int n2 = 0x12345678;
	printf("%llX, %llX", &n2, &n2 + 1); //������ ���� sizeof�� ����ؼ� 1�� ���� ���Ѵ�.
}