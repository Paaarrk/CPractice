#include <iostream>
#include <windows.h>
#include "24_debug_newdelete.h"
#include "018_DebugHeap.h"
#undef new

void* operator new(size_t size, const char* File, int Line)
{
	void* p = malloc(size);
	if (p == nullptr)
		return nullptr;
	if (!AllocInfoHandler::getInstance().push(p, size, File, Line, false))
	{
		free(p);
		return (void*)HANDLER_FULL;
	}
	return p;
}
void* operator new[](size_t size, const char* File, int Line)
{
	void* p = malloc(size);
	if (p == nullptr)
		return nullptr;
	if (!AllocInfoHandler::getInstance().push(p, size, File, Line, true))
	{
		free(p);
		return (void*)HANDLER_FULL;
	}
	return p;
}

#ifdef _MYDEBUG
void operator delete(void* p)
{
	bool success = AllocInfoHandler::getInstance().Delete(&p, false);
	if (success)
	{
		free(p);
	}
}

void operator delete[](void* p)
{
	bool success = AllocInfoHandler::getInstance().Delete(&p, true);
	if (success)
	{
		free(p);
	}
}
#endif

void operator delete(void* p, const char* File, int Line)
{

}
void operator delete[](void* p, const char* File, int Line)
{

}

bool AllocInfoHandler::Delete(void** p, bool array)
{
	if (array == true)
	{	// 배열 델레트
		int idx = find(*p, true);
		if (idx == -1)
		{	//NOALLOC
			write(NOALLOC, p, -1);
			return false;
		}
		else if (AllocInfoHandler::getInstance().getAllocArray(idx) == false)
		{	// 배열이 아닌걸 배열 델레트, 소멸자가 멤버를 건드리지 않으면 가능함
			// 소멸자가 멤버를 건드리면 여기 오기전에 뻑이남
			// 뻑이 안난다면 해제할 수 있게 유도
			// 단, 뒤로 32비트는 4바이트, 64비트는 8바이트 땡겨줘야함 (n이 들어가서)
			// 64비트에서는 너무 오래돌아서 불가능하다고 판단
			write(ARRAY, p, idx);
			arr[idx].ptr = (void*)DELETED;
			//*p = (void*)((char*)*p + sizeof(void*));
			return false;
		}
		else
		{
			//정상
			arr[idx].ptr = (void*)DELETED;	//확인 했으니 체크 안하려고
		}
	}
	else // 일반 델레트
	{
		int idx = find(*p, false);
		if (idx == -1)
		{	//NOALLOC
			write(NOALLOC, *p, -1);
			return false;
		}
		else if (AllocInfoHandler::getInstance().getAllocArray(idx) == false)
		{	// 배열을 일반으로 델레트, 10개라면 9개의 소멸자는 못부르는 상태 -> 누수
			write(ARRAY, *p, idx);
			arr[idx].ptr = (void*)DELETED;
			return false;
		}
		else
		{
			//정상
			arr[idx].ptr = (void*)DELETED;	//확인 했으니 체크 안하려고
		}
	}

	return true;
}

bool AllocInfoHandler::getAllocArray(int idx)	const
{
	return arr[idx].array;
}
void AllocInfoHandler::write(Error err, void* ptr, int idx)
{
	switch (err)
	{
	case NOALLOC:
		fprintf_s(file, "NOALLOC\t[%p]\t\n", ptr);
		break;
	case ARRAY:
		fprintf_s(file, "ARRAY\t[%p]\t [size: %zd]\t %s : %d\n", ptr, arr[idx].size, arr[idx].filename, arr[idx].line);
		break;
	case LEAK:
		fprintf_s(file, "LEAK\t[%p]\t [size: %zd]\t %s : %d\n", ptr, arr[idx].size, arr[idx].filename, arr[idx].line);
		break;
	}
}

bool AllocInfoHandler::push(void* ptr, size_t size, const char* file, int line, bool array)
{
	if (cnt >= MAX_NUM)
		return false;
	arr[cnt].ptr = ptr;
	arr[cnt].size = size;
	strcpy_s(arr[cnt].filename, file);
	arr[cnt].line = line;
	arr[cnt].array = array;
	cnt++;
	return true;
}

/* 인덱스 반환, array는 배열로 해제 할 것인지 여부 */
int AllocInfoHandler::find(void* ptr, bool array)
{
	void* p;
	int index = -1;

	if (array == true)
	{	//배열로 해제
		p = ptr;
		
		for (int i = cnt - 1; i >= 0; i--)
		{
			if (arr[i].ptr == p)
			{
				index = i;
				arr[i].array = true;	//정상적으로 찾았으니까
				break;
			}
		}

		if (index == -1)
		{
			p = (void*)((char*)ptr + sizeof(void*));	// 배열해제의 정체는 일반
			for (int i = cnt - 1; i >= 0; i--)
			{
				if (arr[i].ptr == p)
				{
					index = i;
					arr[i].array = false;
					break;
				}
			}
		}
	}
	else // array false
	{	// 일반 해제
		p = ptr;

		for (int i = cnt - 1; i >= 0; i--)
		{
			if (arr[i].ptr == p)
			{
				index = i;
				arr[i].array = true;
				break;
			}
		}

		if (index == -1)
		{
			// 일반해제에 정체는 배열
			p = (void*)((char*)ptr - sizeof(void*));	
			for (int i = cnt - 1; i >= 0; i--)
			{
				if (arr[i].ptr == p)
				{
					index = i;
					arr[i].array = false;
					break;
				}
			}
		}
	}

	return index;
}
