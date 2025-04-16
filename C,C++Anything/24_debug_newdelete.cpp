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
	{	// �迭 ����Ʈ
		int idx = find(*p, true);
		if (idx == -1)
		{	//NOALLOC
			write(NOALLOC, p, -1);
			return false;
		}
		else if (AllocInfoHandler::getInstance().getAllocArray(idx) == false)
		{	// �迭�� �ƴѰ� �迭 ����Ʈ, �Ҹ��ڰ� ����� �ǵ帮�� ������ ������
			// �Ҹ��ڰ� ����� �ǵ帮�� ���� �������� ���̳�
			// ���� �ȳ��ٸ� ������ �� �ְ� ����
			// ��, �ڷ� 32��Ʈ�� 4����Ʈ, 64��Ʈ�� 8����Ʈ ��������� (n�� ����)
			// 64��Ʈ������ �ʹ� �������Ƽ� �Ұ����ϴٰ� �Ǵ�
			write(ARRAY, p, idx);
			arr[idx].ptr = (void*)DELETED;
			//*p = (void*)((char*)*p + sizeof(void*));
			return false;
		}
		else
		{
			//����
			arr[idx].ptr = (void*)DELETED;	//Ȯ�� ������ üũ ���Ϸ���
		}
	}
	else // �Ϲ� ����Ʈ
	{
		int idx = find(*p, false);
		if (idx == -1)
		{	//NOALLOC
			write(NOALLOC, *p, -1);
			return false;
		}
		else if (AllocInfoHandler::getInstance().getAllocArray(idx) == false)
		{	// �迭�� �Ϲ����� ����Ʈ, 10����� 9���� �Ҹ��ڴ� ���θ��� ���� -> ����
			write(ARRAY, *p, idx);
			arr[idx].ptr = (void*)DELETED;
			return false;
		}
		else
		{
			//����
			arr[idx].ptr = (void*)DELETED;	//Ȯ�� ������ üũ ���Ϸ���
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

/* �ε��� ��ȯ, array�� �迭�� ���� �� ������ ���� */
int AllocInfoHandler::find(void* ptr, bool array)
{
	void* p;
	int index = -1;

	if (array == true)
	{	//�迭�� ����
		p = ptr;
		
		for (int i = cnt - 1; i >= 0; i--)
		{
			if (arr[i].ptr == p)
			{
				index = i;
				arr[i].array = true;	//���������� ã�����ϱ�
				break;
			}
		}

		if (index == -1)
		{
			p = (void*)((char*)ptr + sizeof(void*));	// �迭������ ��ü�� �Ϲ�
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
	{	// �Ϲ� ����
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
			// �Ϲ������� ��ü�� �迭
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
