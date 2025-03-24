#include <windows.h>
#include <stdio.h>


void* malloc_debug_overflow(size_t t)
{
	void* allocbase = VirtualAlloc(NULL, ((t + 4095) & (~4095)) + 4096, MEM_RESERVE, PAGE_READWRITE);
	if (allocbase == NULL)
		return NULL;
	VirtualAlloc(allocbase, (t + 4095) & (~4095), MEM_COMMIT, PAGE_READWRITE);
	void* p = VirtualAlloc((char*)allocbase + ((t + 4095) & (~4095)),4096 ,MEM_COMMIT, PAGE_NOACCESS);

	return (void*)((char*)p - t);
}
void* malloc_debug_underflow(size_t t)
{
	void* allocbase = VirtualAlloc(NULL, ((t + 4095) & (~4095)) + 4096, MEM_RESERVE, PAGE_READWRITE);
	if (allocbase == NULL)
		return NULL;
	VirtualAlloc(allocbase, 4096, MEM_COMMIT, PAGE_NOACCESS);
	VirtualAlloc((char*)allocbase + 4096, (t + 4095) & (~4095), MEM_COMMIT, PAGE_READWRITE);
}
int free_debug_heap(void* p)
{
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery(p, &mbi, sizeof(mbi));
	if (VirtualFree(mbi.AllocationBase, 0, MEM_RELEASE) == TRUE)
	{
		return 0;
	}
	else
		return 1;
}