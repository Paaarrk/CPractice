#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include "Ch09.h"

int _ABOVE_NORMAL_PRIORITY_CLASS()
{
	STARTUPINFO siNormal = { 0, };
	siNormal.cb = sizeof(siNormal);
	PROCESS_INFORMATION piNormal;
	TCHAR commandOne[] =
		_T("NORMAL_PRIORITY_CLASS.exe");
	
	STARTUPINFO siBelow = { 0, };
	siBelow.cb = sizeof(siBelow);
	PROCESS_INFORMATION piBelow;
	TCHAR commandTwo[] = _T("BELOW_NORMAL_PRIORITY_CLASS.exe");

	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);

	CreateProcess(NULL, commandOne, NULL, NULL, TRUE, 0, NULL, NULL,
		&siNormal, &piNormal);
	CreateProcess(NULL, commandTwo, NULL, NULL, TRUE, 0, NULL, NULL,
		&siBelow, &piBelow);

	CloseHandle(piNormal.hProcess);
	CloseHandle(piNormal.hThread);
	CloseHandle(piBelow.hProcess);
	CloseHandle(piBelow.hThread);
	
	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++);

		//Sleep(10);

		_fputts(_T("ABOVE_NORMAL_PRIORITY_CLASS Process\n"), stdout);
	}
	return 0;
}

int _NORMAL_PRIORITY_CLASS()
{
	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);

	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++);

		//Sleep(10);
		
		_fputts(_T("NORMAL_PRIORITY_CLASS Process\n"), stdout);
	}
	return 0;
}

int _BELOW_NORMAL_PRIORITY_CLASS()
{
	SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);

	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++);

		//Sleep(10);

		_fputts(_T("BELOW_NORMAL_PRIORITY_CLASS Process\n"), stdout);
	}
}