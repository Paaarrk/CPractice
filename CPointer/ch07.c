#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
/*
** 포인터와 구조체 **
* My Result *
1)	연산자 우선 순위 : . ->	[], . -> & * -> +-
2)	구조체의 변수명은 메모리는 모른다. 구조체의 주소로부터 얼마나 멀리 떨어져 있는지만 알 뿐이다.
	-> 어셈블리로 보면 배열같은 느낌을 받음
3)	어셈블리 확인 결과 ( )->x 와 (*()).x 와 [].x 는 똑같이 바꿔준다 (속도 차이 x)

1.	구조체의 주소 저장하기
 
2.	다차원 포인터, 배열, 구조체

3.	구조체 멤버로 주소 저장하기

4.	자신의 주소를 저장하는 구조체

*/
static struct _point
{
	int x;
	int y;
};

void Ch07_01()
{
	typedef unsigned int uint;
	struct _point s = {10, 10};
	struct _point* sp = &s;
	
	printf("%d %d \n", (uint)s.x, (uint)s.y);
	printf("%d %d \n", (uint)sp->x, (uint)sp->y);
	printf("%d %d \n", (uint)(*sp).x, (uint)(*sp).y);
	fputs("\n", stdout);

	struct _point sarr[5] = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 };
	printf("{%d, %d}\n", sarr[0].x, sarr[0].y);
	printf("{%d, %d}\n", sarr[1].x, sarr[1].y);
	printf("{%d, %d}\n", sarr[2].x, sarr[2].y);
	printf("{%d, %d}\n", sarr[3].x, sarr[3].y);
	printf("{%d, %d}\n", sarr[4].x, sarr[4].y);
	puts("-------------------------------\n");
	printf("{%d, %d}\n", sarr->x, sarr->y);
	printf("{%d, %d}\n", (sarr + 1)->x, (sarr + 1)->y);	//sarr + 1 * sizeof(*sarr) = sarr + 8
	printf("{%d, %d}\n", (sarr + 2)->x, (sarr + 2)->y);	//sarr + 2 * sizeof(*sarr) = sarr + 16
	printf("{%d, %d}\n", (sarr + 3)->x, (sarr + 3)->y);	//sarr + 3 * sizeof(*sarr) = sarr + 24
	printf("{%d, %d}\n", (sarr + 4)->x, (sarr + 4)->y);	//sarr + 4 * sizeof(*sarr) = sarr + 32
	puts("-------------------------------\n");
	printf("{%d, %d}\n", (*sarr).x, (*sarr).y);
	printf("{%d, %d}\n", (*(sarr + 1)).x, (*(sarr + 1)).y);
	printf("{%d, %d}\n", (*(sarr + 2)).x, (*(sarr + 2)).y);
	printf("{%d, %d}\n", (*(sarr + 3)).x, (*(sarr + 3)).y);
	printf("{%d, %d}\n", (*(sarr + 4)).x, (*(sarr + 4)).y);
	
}

void Ch07_02()
{
	struct _point sarr[5] = { 1,1,2,2,3,3,4,4,5,5 };
	int* ptr = (int*)sarr;	//위험한 코드, 지금 4바이트에 맞는 변수를 써서가능할 뿐

	for (int i = 9; i != 0; i--)
	{
		printf("%d\n", *(ptr + 9 - i));
	}
}

void Ch7_03()
{
	struct _point sarr[5] = { 1,1,2,2,3,3,4,4,5,5 };
	for (int i = 4; i >= 0; i--)
	{
		printf("{%d, %d} \n", sarr[i].x, (sarr + i)->y);
	}
}

void Ch7_04()
{	// sizeof 예상하기 : 32비트 기준
	struct _point p1[] = { 1,1,2,2 };
	struct _point* p2 = &p1;
	int a = 1;
	int* b = &a;
	printf("%d = %d\n", sizeof(p1), 16);
	printf("%d = %d\n", sizeof(p2), 4);
	printf("%d = %d\n", sizeof(*p1), 8);
	printf("%d = %d\n", sizeof(*p2), 8);
	printf("%d = %d\n", sizeof(p1[1].x), 4);
	printf("%d = %d\n", sizeof(p2[1].x), 4);
	printf("%d = %d\n", sizeof(p1[1]), 8);
	printf("%d = %d\n", sizeof(p2[1]), 8);
	printf("%d = %d\n", sizeof(p2[1].x), 4);
	printf("%x, %x\n", (int)p1, (int)(p1 + 1));
	printf("%x, %x\n", (int)p1, (int)(&p1 + 1));
	printf("%x, %x\n", (int)p1, (int)(p2 + 1));
	printf("%x, %x\n", (int)p1, (int)(&p2 + 1));
	printf("%x, %x\n", (int)p1, (int)p1 + 1);
	printf("%x, %x\n", (int)a, (int)(a + 1));
	printf("%x, %x\n", (int)b, (int)(b + 1));
	printf("%x, %x\n", (int)&a, (int)(&a + 1));
	printf("%x, %x\n", (int)&b, (int)(&b + 1));
}

static struct _d {
	char* x;
	int* y;
	char z[4];
};
void Ch7_05()
{
	struct _d x, *y;
	y = &x;
	printf("%x, %x\n", (int)y->x, (int)y->y);

	//struct _point s1 = { 1, 1 };
	//struct _point* sp = &s1;
	//struct _point** spp = &sp;
	//
	//printf("(%d, %d)\n", s1.x, s1.y);
	//printf("(%d, %d)\n", sp->x, sp->y);
	//printf("(%d, %d)\n", (*spp)->x, (*spp)->y);
	//printf("(%d, %d)\n", (**spp).x, (**spp).y);
}