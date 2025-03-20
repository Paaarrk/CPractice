#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <process.h>
#include <tchar.h>
#include "Ch13.h"

#define NUM_OF_GATE	10
CRITICAL_SECTION gCriticalSection;
LONG gTotalCount;

static void IncreaseCount()
{
	EnterCriticalSection(&gCriticalSection);
	gTotalCount++;
	_tprintf_s(_T("%10d\n"), gTotalCount);
	LeaveCriticalSection(&gCriticalSection);
}

static unsigned int __stdcall ThreadProc(LPVOID lpParam)
{
	for (DWORD i = 0; i < 1000; i++)
	{
		IncreaseCount();
	}
	return 0;
}

int UseCriticalSection()
{
	DWORD dwThreadId[NUM_OF_GATE];
	HANDLE hThread[NUM_OF_GATE];

	InitializeCriticalSection(&gCriticalSection);
	for (DWORD i = 0; i < NUM_OF_GATE; i++)
	{
		hThread[i] = (HANDLE)_beginthreadex(
			NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED,
			(unsigned*)&dwThreadId[i]);

		if (hThread[i] == NULL)
		{
			_tprintf_s(_T("Thread creation fault! \n"));
			return -1;
		}
	}

	for (DWORD i = 0; i < NUM_OF_GATE; i++)
	{
		ResumeThread(hThread[i]);
	}

	WaitForMultipleObjects(
		NUM_OF_GATE, hThread, TRUE, INFINITE
	);

	_tprintf_s(_T("Total Count: %d \n"), gTotalCount);
	for (DWORD i = 0; i < NUM_OF_GATE; i++)
	{
		CloseHandle(hThread[i]);
	}

	DeleteCriticalSection(&gCriticalSection);
	return 0;
}