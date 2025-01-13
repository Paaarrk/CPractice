#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
/*
** 포인터와 구조체 **
* My Result *
1)	연산자 우선 순위 : . ->	[], . -> & * -> +-
2)	구조체의 변수명은 메모리는 모른다. 구조체의 주소로부터 얼마나 멀리 떨어져 있는지만 알 뿐이다.
	-> 어셈블리로 보면 배열같은 느낌을 받음

1.	구조체의 주소 저장하기
 
2.	다차원 포인터, 배열, 구조체

3.	구조체 멤버로 주소 저장하기

4.	자신의 주소를 저장하는 구조체

*/
struct _point
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