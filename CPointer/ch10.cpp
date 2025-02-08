#include <stdio.h>
#include <malloc.h>

/*
10장. 동적 메모리, 가변인자, const상수

1. 동적 메모리
	void* malloc(size_t n), void free(void* memblock)
	void* _aligned_malloc(size_t size, size_t alignment), void _aligned_free(void* memblock)
2. 가변인자

3. const상수

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
	
}