#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/*
** 구조체와 공용체 **
* MyResult *
1)	&는 차원을 올림, *는 차원을 낮춤, .은 동일 차원(타입 다름)(배열의 []는 타입 낮춤)
2)	구조체는 배열과 닮았다
3)	공용체는 참조와 닮았다(ReName)
4)	공용체는 잘 이용하면 읽는 방법을 통해 재미있는 결과를 낼 수 있다.

1.	구조체 다루기
	1) 타입이 다른 두개 이상의 변수를 사용하면 가장 큰 타입 기준으로 사이즈가 계산이 된다. (아마도 4바이트씩 잘라쓰기 위해서?)
	2) 변수의 위치를 어디에 두느냐에 따라 사이즈가 달라진다.
2.	공용체 다루기

3.	구조체와 공용체의 주소
	1) 변수 명 자체는 배열과 달리 주소를 나타내지 않는다.
	2) 공용체의 경우 변수자체가 내부의 저장 정보를 출력한다.
	3) 구조체의 경우 변수자체는 똥값을 가진다. (무슨 값인지는 모르겠다)
	   -> 8바이트 구조체의 경우 값을 출력함.
	4) np + n * (sizeof(*np))는 여전히 유효
*/



void Ch06_01()
{
	struct i_point {
		int x;
		int y;
	};

	struct d_point {
		double x;
		double y;
	};

	struct c_point {
		short x;
		long long y;
	};

	struct i_point ipnt = { 10, 10 };
	struct d_point dpnt = { 10.0, 10.0 };
	struct c_point cpnt = { 0x4321, 0x8877665544332211 };

	printf("%d %d %d\n\n", (int)sizeof(ipnt), (int)sizeof(dpnt), (int)sizeof(cpnt));
	printf("왜 c_point는 10이 아니라 16?\n");
	printf("%d %d\n\n", (int)sizeof(cpnt.x), (int)sizeof(cpnt.y));
	printf("c_point의 주소 체계를 확인해보자\n");
	unsigned char* cp = (char*)&cpnt;
	for (int i = 0; i < 16; i++)
	{
		printf("%x \n", cp[i]);
	}
	printf("아! 공백자리를 놓는구나!\n\n");

	printf("그렇다면 cp[3 ~ 7]의 값을 수정해도 값에 변화가 없나? \n");
	*(cp + 3) = 0xdd;
	printf("%x, %llx\n", (int)cpnt.x, cpnt.y);
	printf("변화가 없구나\n\n");
	printf("그렇다면 cpnt.x를 long long 만큼 읽는다면? \n");
	long long* ip = (long long*)&cpnt.x;
	printf("%llx \n", *ip);
	printf("수정한 값을 볼 수 있다. 즉, 구조체 남은 바이트(6바이트)도 포인터를 사용하면 활용할 수 있다\n");


	struct id_point {
		int x;
		double y;
	};
	struct id_point idpnt = { 10, 10.0 };
	// 이런 경우는?
	printf("%d \n\n", (int)sizeof(idpnt));
	unsigned int* uip = (unsigned int*)&idpnt;
	for (int i = 0; i < 4; i++)
	{
		printf("%x\t", *(uip + i));
	}

	/*
	4바이트 블럭
	-idpnt-
	[ 10  ]
	[trash]
	[ 10  ]
	[ .0  ]
	*/
}

void Ch06_02()
{
	union mix {
		long long ll;
		int i[2];
		short s[4];
		char c[8];
	};

	union mix m = { 0x0047464544434241 };
	printf("%llX\n", m.ll);
	printf("%X %X\n", m.i[0], m.i[1]);
	printf("%X %X %X %X\n", m.s[0], m.s[1], m.s[2], m.s[3]);
	printf("%X %X %X %X %X %X %X %X\n\n", m.c[0], m.c[1], m.c[2], m.c[3], m.c[4], m.c[5], m.c[6], m.c[7]);
	
	for (int i = 0; i < 8; i++)
	{
		printf("%s \n", m.c + i);
	}


}

void Ch06_03()
{
	union u {
		int i;
		char c[4];
	};

	struct s1 {
		short y;
		int x;
		char z;
	};

	struct s2 {
		int x;
		short y;
		char z;
	};

	union u u = { 0x00434241 };
	struct s1 s1 = { 0x4645, 0x44434241, 0x00 };
	struct s2 s2 = { 0x44434241, 0x4645, 0x00 };

	printf("%d == 4 %d == 12 %d == 8\n\n", (int)sizeof(u), (int)sizeof(s1), (int)sizeof(s2));

	// 메모리 구조
	printf("메모리 구조\n");
	unsigned char* up = (unsigned char*)&u;
	unsigned char* s1p = (unsigned char*)&s1;
	unsigned char* s2p = (unsigned char*)&s2;
	for (int i = 0; i < sizeof(u); i++)
	{
		printf("%x \n", (unsigned int)up[i]);
	}
	printf("\n");
	for (int i = 0; i < sizeof(s1); i++)
	{
		printf("%x \n", (unsigned int)s1p[i]);
	}
	printf("\n");
	for (int i = 0; i < sizeof(s2); i++)
	{
		printf("%x \n", (unsigned int)s2p[i]);
	}
	printf("\n");
	// 포인터 다루기
	printf("%llx %llx\t %llx %llx\t %llx %llx\n\n", u, (long long)&u, s1, (long long)& s1, s2, (long long)&s2);

	char* cup = (char*)&u;
	char* cs1p = (char*)&s1;
	char* cs2p = (char*)&s2;
	// 문자열로 읽기
	printf("%s\t%s\t%s\n\n", cup, cs1p, cs2p);
	
	//주소 확인하기
	// 공용체의 주소
	printf("%llx %llx %llx %llx \n\n", &u, &u.i, u.c, &u.c + 1, u.c + 1);
	//sizeof(u.c) = 4이므로 &u.c + 1 =  u.c + 4

	// 구조체의 주소
	printf("%llx %llx %llx \n\n", &s2.x, &s2.y, &s2.z);
	printf("%llx %llx", &s2.y + 1, &s2.z + 1);
}