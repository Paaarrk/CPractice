#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
#include "ch10.h"

//t 는 type ap는 주소, ap를 t type으로 형변환 후 값을 읽음
#define myap(ap, t)	\
	(*((t*)((ap += sizeof(t)) - sizeof(t))))
	

/*
10장. 동적 메모리, 가변인자, const상수

1. 동적 메모리
	void* malloc(size_t n), void free(void* memblock)
	void* _aligned_malloc(size_t size, size_t alignment), void _aligned_free(void* memblock)
2. 가변인자
	<매크로를 사용하지 않을 시>
	함수의 인자를 고정시키지 않고, 개수와 형태를 다르게 호출
	_cdecl의 특성을 활용
	-> 호출 시 매개변수를 오른쪽에서 왼쪽으로 전달(RTL)
		-> 인자 전달 시 스택의 가장 위에 첫번째 매개변수
	-> 변수의 정리는 Caller가 함. 호출된 함수는 정리가 필요없음.
	-> ebp+8에 첫번째 변수가 있으므로 그것을 기준으로 변수를 사용
	-> '몇 개'의 변수가 전달되었는지 첫번째 인자로 반드시 전달해야함

	<매크로 사용>
	va_list	(=char*)
	va_start(va_list, n)
	va_end(va_list)

3. const상수
	타입을 빼고 const가 *에 붙으면 값을 수정하지 못하고, 
	const가 변수에 붙으면 변수를 수정하지 못한다.
*/
typedef struct _point {
	int x;
	int y;
};
typedef struct  alignas(32) _aligned_point {
	alignas(32) int x;
	int y;
};

void Ch10_01()
{
	int* a = (int*)malloc(sizeof(int));
	int* arr = (int*)malloc(sizeof(int) * 10);	//arr[10]
	int(*darr)[2] = (int(*)[2])malloc(sizeof(int) * 2 * 2);	//darr[2][2]
	alignas(32)int* b = (int*)_aligned_malloc(sizeof(b), 32);
	_aligned_point* parr = (_aligned_point*)_aligned_malloc(sizeof(_aligned_point) * 2, sizeof(_aligned_point));
	parr->x = 9;
	parr->y = 7;
	parr[1].x = 6;
	parr[2].y = 5;
	free(a);
	free(arr);
	free(darr);
	_aligned_free(b);
	_aligned_free(parr);
}

int _cdecl VariadicFunction(int n, ...)
{
	int result = 0;
	for (int i = n; i != 0; i--)
	{
		result += *(&n + i);
	}

	return result;
}

int _cdecl VaSum(int n, ...)
{
	int sum = 0;
	va_list ap;
	va_start(ap, n);

	for (int i = 0; i < n; i++)
	{
		sum += myap(ap, int);
	}
	va_end(ap);
	return sum;
}

void minprintf(const char* fmt, ...)
{
	int i = 0;
	va_list ap;
	va_start(ap, fmt);
	for (i; fmt[i]; i++)	//fmt[i] != 0
	{
		if (fmt[i] != '%')
			putchar(fmt[i]);
		else
			switch (fmt[++i])
			{
			case 'c':
				printf_s("%c", va_arg(ap, char));
				break;
			case 'd':
				printf_s("%d", myap(ap, int));
				break;
			case 's':
				printf_s("%s", myap(ap, char*));
				break;
			}
	}
	va_end(ap);
	return;
}

void Ch10_02()
{
	int sum = VariadicFunction(5, 1, 2, 3, 4, 5);
	printf_s("총 합: %d\n", sum);
	int sum2 = VaSum(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
	printf_s("총 합: %d\n", sum2);

	minprintf("%d + %d = %d\n", 10, 20, 10 + 20);
	minprintf("%s = ABC\n", "ABC");
	minprintf("%c%c%c\n", 'A', 'B', 'c');
}