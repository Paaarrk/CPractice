#ifndef __DEBUG_HEAP_H__
#define __DEBUG_HEAP_H__

//#define _DEBUG_OVER
//#define _DEBUG_UNDER
#ifdef _DEBUG_OVER
#define malloc(size)	malloc_debug_overflow(size)
#define free(size)		free_debug_heap(size)
#elif defined(_DEBUG_UNDER)
#define malloc(size)	malloc_debug_underflow(size)
#define free(size)		free_debug_heap(size)
#else
#define malloc(size)	malloc(size)
#define free(size)		free(size)
#endif
void* malloc_debug_overflow(size_t t);
void* malloc_debug_underflow(size_t t);
int free_debug_heap(void* p);

#endif
