#include <iostream>
#include <tchar.h>
#include <Windows.h>


void Ex01()
{
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++);

		_fputts(_T("Operation2.exe \n"), stdout);
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++);
	}
}