#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/*
������ �޸𸮿� �Ҵ�ȴ�. 
������ �̸��� �г���, ������ �ּҴ� ���̵� ����
������ �ڷ������� �޸� ������ ũ��� ���¸� ��Ÿ����.
sizeof() �� �����ڷ�, �����Ͻð��� ������ ġȯ�ȴ�.
*/

void Ch01_01()
{	
	char c = 'A';
	char* cp = &c;
	int i = 15;
	int* ip = &i;
	long l = 13;
	long* lp = &l;
	long long ll = 14;
	long long* llp = &ll;
	float f = 14.8f;
	float* fp = &f;
	double d = 14.8;
	double* dp = &d;
	long double ld = 14.8l;
	long double* ldp = &ld;

	printf("--- 64��Ʈ ���μ��� ���� (������ ���� long�� 4byte) --- \n");
	printf("char�� ������: %d����Ʈ, char�� ����: %c, char�� �ּ�: %llX \n", sizeof(c), c, &c);
	printf("char������ ������: %d����Ʈ, char�������� ���尪: %llX, char�� �ּ�: %llX \n", sizeof(cp), cp, &cp);
	printf("[cp] -> [c] -> Mem[A]\n\n");
	printf("int�� ������: %d����Ʈ, int�� ����: %d, int�� �ּ�: %llX \n", sizeof(i), i, &i);
	printf("int������ ������: %d����Ʈ, int�������� ���尪: %llX, int�� �ּ�: %llX \n", sizeof(ip), ip, &ip);
	printf("[ip] -> [i] -> Mem[15]\n\n");
	printf("long�� ������: %d����Ʈ, long�� ����: %d, long�� �ּ�: %llX \n", sizeof(l), l, &l);
	printf("long������ ������: %d����Ʈ, long�������� ���尪: %llX, long�� �ּ�: %llX \n", sizeof(lp), lp, &lp);
	printf("[lp] -> [l] -> Mem[13]\n\n");
	printf("longlong�� ������: %d����Ʈ, longlong�� ����: %d, longlong�� �ּ�: %llX \n", sizeof(ll), ll, &ll);
	printf("longlong������ ������: %d����Ʈ, longlong�������� ���尪: %llX, longlong�� �ּ�: %llX \n", sizeof(llp), llp, &llp);
	printf("[llp] -> [ll] -> Mem[14]\n\n");
	printf("longlong�� �������ּҸ� ���� �� �� ���� ��?\n");
	ll = cp;
	printf("ll ��: %llX\n", ll);
	printf("ll char*�� ����ȯ �� �� ����: %c\n\n", *(char*)ll);
	printf("float�� ������: %d����Ʈ, float�� ����: %f, float�� �ּ�: %llX \n", sizeof(f), f, &f);
	printf("float������ ������: %d����Ʈ, float�������� ���尪: %llX, float�� �ּ�: %llX \n", sizeof(fp), fp, &fp);
	printf("[fp] -> [f] -> Mem[14.8]\n\n");
	printf("double�� ������: %d����Ʈ, double�� ����: %lf, double�� �ּ�: %llX \n", sizeof(d), d, &d);
	printf("double������ ������: %d����Ʈ, double�������� ���尪: %llX, double�� �ּ�: %llX \n", sizeof(dp), dp, &dp);
	printf("[dp] -> [d] -> Mem[14.8]\n\n");
	printf("longdouble�� ������: %d����Ʈ, longdouble�� ����: %llf, longdouble�� �ּ�: %llX \n", sizeof(ld), ld, &ld);
	printf("longdouble������ ������: %d����Ʈ, longdouble�������� ���尪: %llX, longdouble�� �ּ�: %llX \n", sizeof(ldp), ldp, &ldp);
	printf("[ldp] -> [ld] -> Mem[14.8]\n\n");
}

void Ch01_02()
{
	// 1. �ּ��� ��.����
	/*
	�ּ��� ���� 
	�ڷ����� �ּ�(n + 1����) +- ���� * sizeof(�ڷ���(n����)) = �ڷ����� �ּ� 
	*/
	char c = 'A';
	short s = 9;
	int i = 10;
	long l = 11;
	long long ll = 12;

	printf("char �ּ�:\t%lld\nchar �ּ� +1:\t%lld \n\n", &c, (& c) + 1);
	printf("short �ּ�:\t%lld\nshort �ּ� +1:\t%lld \n\n", &s, (& s) + 1);
	printf("int �ּ�:\t%lld\nint �ּ� +1:\t%lld \n\n", &i, (& i) + 1);
	printf("long �ּ�:  \t%lld\nlong �ּ� +1:\t%lld \n\n", &l, (& l) + 1);
	printf("longlong �ּ�:\t\t%lld\nlonglong �ּ� +1:\t%lld \n\n", &ll, (& ll) + 1);

	float f = 14.8f;
	double d = 14.8;
	printf("float �ּ�:\t\t%lld\nfloat �ּ� + 1: \t%lld \n\n", &f, (&f) + 1);
	printf("double �ּ�:\t\t%lld\ndouble �ּ� + 1: \t%lld \n\n", &d, (&d) + 1);
	

	// 2. �ּҸ� ������ ���� �о��
	/*
	-- STACK --	(GB : Garbage)
	[   44   ] -- 0x00  char
	[   33   ] -- 0x01      short
	[   22   ] -- 0x02           
	[   11   ] -- 0x03            int, long
	[   GB   ] -- 0x04
	[   GB   ] -- 0x05
	[   GB   ] -- 0x06
	[   GB   ] -- 0x07                      longlong
	*/
	int n = 0x11223344;
	printf("char�� �б�: \t%X, %X, %X, %X\n\n", *(char*)&n, *((char*)&n + 1), *((char*)&n + 2), *((char*)&n + 3));
	printf("short�� �б�: \t%X, %X \n\n", *(short*)&n, *((short*)&n + 1));
	printf("int �� �б�: \t%X \n\n", *(int*)&n);
	printf("long �� �б�: \t%lX \n\n", *(long*)&n);
	printf("longlong �� �б�: \t%llX (������ ���� ���� ���´�)\n\n", *(long long*)&n);

	// 3. �迭ó�� �ּҸ� �о��
	long long nn= 0x1122334455667788;
	printf("Stack�� ����\n");
	for (int i = 0; i < 8; i++)
	{
		printf("[ %X ]\n", ((char*)&nn)[i]);
	}
	printf("\n�����б�\n");
	printf("[   %X   ]\n", *(short*)&nn);
	printf("[ %X ]\n", *(int*)((short*)&nn + 1));
	printf("[   %X   ]\n", *((short*)&nn) + 3);

	// ++ �� -- ���� ������ ����� �Ұ��� �� ����
	/*
	1. ++,-- �� ������ ����Ǵ� ������ �̱� �����̴�.
	2. ������ ������� �����ϴ�. ������ &�� ���� �ּҿ��� ����� �Ұ����ϴ�.
	*/

}


