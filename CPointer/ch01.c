#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/*
변수는 메모리에 할당된다. 
변수의 이름은 닉네임, 변수의 주소는 아이디 느낌
변수는 자료형으로 메모리 공간의 크기와 형태를 나타낸다.
sizeof() 는 연산자로, 컴파일시간에 값으로 치환된다.
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

	printf("--- 64비트 프로세서 기준 (윈도우 기준 long은 4byte) --- \n");
	printf("char의 사이즈: %d바이트, char의 문자: %c, char의 주소: %llX \n", sizeof(c), c, &c);
	printf("char포인터 사이즈: %d바이트, char의포인터 저장값: %llX, char의 주소: %llX \n", sizeof(cp), cp, &cp);
	printf("[cp] -> [c] -> Mem[A]\n\n");
	printf("int의 사이즈: %d바이트, int의 문자: %d, int의 주소: %llX \n", sizeof(i), i, &i);
	printf("int포인터 사이즈: %d바이트, int의포인터 저장값: %llX, int의 주소: %llX \n", sizeof(ip), ip, &ip);
	printf("[ip] -> [i] -> Mem[15]\n\n");
	printf("long의 사이즈: %d바이트, long의 문자: %d, long의 주소: %llX \n", sizeof(l), l, &l);
	printf("long포인터 사이즈: %d바이트, long의포인터 저장값: %llX, long의 주소: %llX \n", sizeof(lp), lp, &lp);
	printf("[lp] -> [l] -> Mem[13]\n\n");
	printf("longlong의 사이즈: %d바이트, longlong의 문자: %d, longlong의 주소: %llX \n", sizeof(ll), ll, &ll);
	printf("longlong포인터 사이즈: %d바이트, longlong의포인터 저장값: %llX, longlong의 주소: %llX \n", sizeof(llp), llp, &llp);
	printf("[llp] -> [ll] -> Mem[14]\n\n");
	printf("longlong에 포인터주소를 저장 할 수 있을 까?\n");
	ll = cp;
	printf("ll 값: %llX\n", ll);
	printf("ll char*로 형변환 후 값 추출: %c\n\n", *(char*)ll);
	printf("float의 사이즈: %d바이트, float의 문자: %f, float의 주소: %llX \n", sizeof(f), f, &f);
	printf("float포인터 사이즈: %d바이트, float의포인터 저장값: %llX, float의 주소: %llX \n", sizeof(fp), fp, &fp);
	printf("[fp] -> [f] -> Mem[14.8]\n\n");
	printf("double의 사이즈: %d바이트, double의 문자: %lf, double의 주소: %llX \n", sizeof(d), d, &d);
	printf("double포인터 사이즈: %d바이트, double의포인터 저장값: %llX, double의 주소: %llX \n", sizeof(dp), dp, &dp);
	printf("[dp] -> [d] -> Mem[14.8]\n\n");
	printf("longdouble의 사이즈: %d바이트, longdouble의 문자: %llf, longdouble의 주소: %llX \n", sizeof(ld), ld, &ld);
	printf("longdouble포인터 사이즈: %d바이트, longdouble의포인터 저장값: %llX, longdouble의 주소: %llX \n", sizeof(ldp), ldp, &ldp);
	printf("[ldp] -> [ld] -> Mem[14.8]\n\n");
}

void Ch01_02()
{
	// 1. 주소의 가.감산
	/*
	주소의 연산 
	자료형의 주소(n + 1차원) +- 정수 * sizeof(자료형(n차원)) = 자료형의 주소 
	*/
	char c = 'A';
	short s = 9;
	int i = 10;
	long l = 11;
	long long ll = 12;

	printf("char 주소:\t%lld\nchar 주소 +1:\t%lld \n\n", &c, (& c) + 1);
	printf("short 주소:\t%lld\nshort 주소 +1:\t%lld \n\n", &s, (& s) + 1);
	printf("int 주소:\t%lld\nint 주소 +1:\t%lld \n\n", &i, (& i) + 1);
	printf("long 주소:  \t%lld\nlong 주소 +1:\t%lld \n\n", &l, (& l) + 1);
	printf("longlong 주소:\t\t%lld\nlonglong 주소 +1:\t%lld \n\n", &ll, (& ll) + 1);

	float f = 14.8f;
	double d = 14.8;
	printf("float 주소:\t\t%lld\nfloat 주소 + 1: \t%lld \n\n", &f, (&f) + 1);
	printf("double 주소:\t\t%lld\ndouble 주소 + 1: \t%lld \n\n", &d, (&d) + 1);
	

	// 2. 주소를 가지고 값을 읽어보기
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
	printf("char로 읽기: \t%X, %X, %X, %X\n\n", *(char*)&n, *((char*)&n + 1), *((char*)&n + 2), *((char*)&n + 3));
	printf("short로 읽기: \t%X, %X \n\n", *(short*)&n, *((short*)&n + 1));
	printf("int 로 읽기: \t%X \n\n", *(int*)&n);
	printf("long 로 읽기: \t%lX \n\n", *(long*)&n);
	printf("longlong 로 읽기: \t%llX (쓰레기 값도 같이 나온다)\n\n", *(long long*)&n);

	// 3. 배열처럼 주소를 읽어보자
	long long nn= 0x1122334455667788;
	printf("Stack의 구성\n");
	for (int i = 0; i < 8; i++)
	{
		printf("[ %X ]\n", ((char*)&nn)[i]);
	}
	printf("\n섞어읽기\n");
	printf("[   %X   ]\n", *(short*)&nn);
	printf("[ %X ]\n", *(int*)((short*)&nn + 1));
	printf("[   %X   ]\n", *((short*)&nn) + 3);

	// ++ 와 -- 같은 연산자 사용이 불가능 한 이유
	/*
	1. ++,-- 는 변수에 적용되는 연산자 이기 때문이다.
	2. 포인터 변수라면 가능하다. 하지만 &로 꺼낸 주소에는 사용이 불가능하다.
	*/

}


