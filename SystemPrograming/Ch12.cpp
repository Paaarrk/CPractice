#include <windows.h>
#include <iostream>
#include "Ch12.h"
#include "tchar.h"
#include "process.h"

static DWORD __stdcall ThreadProc(LPVOID lpParam)
{
	DWORD* nPtr = (DWORD*)lpParam;

	DWORD numOne = *nPtr;
	DWORD numTwo = *(nPtr + 1);

	DWORD total = 0;
	for (DWORD i = numOne; i <= numTwo; i++)
	{
		total += i;
	}
	return total;
}
int ThreadAdder1()
{
	DWORD dwThreadID[3];
	HANDLE hThread[3];

	DWORD paramThread[] = { 1, 3, 4, 7, 8, 10 };
	DWORD total = 0;
	DWORD result = 0;

	hThread[0] =
		CreateThread(
			NULL, 0, ThreadProc, (LPVOID)(&paramThread[0]),
			0, &dwThreadID[0]);

	hThread[1] =
		CreateThread(NULL, 0, ThreadProc, (LPVOID)(&paramThread[2])
			, 0, &dwThreadID[1]);

	hThread[2] =
		CreateThread(NULL, 0, ThreadProc, (LPVOID)(&paramThread[4]),
			0, &dwThreadID[2]);

	if (hThread[0] == NULL || hThread[1] == NULL || hThread[2] == NULL)
	{
		_tprintf_s(_T("Thread creation fault! \n"));
		return -1;
	}

	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	GetExitCodeThread(hThread[0], &result);
	total += result;
	GetExitCodeThread(hThread[1], &result);
	total += result;
	GetExitCodeThread(hThread[2], &result);
	total += result;

	_tprintf_s(_T("total (1 ~ 10): %d\n"), total);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);
	return 0;
}

static int total = 0;
static DWORD __stdcall ThreadProc2(LPVOID lpParam)
{
	DWORD* ptr = (DWORD*)lpParam;
	
	DWORD start = ptr[0];
	DWORD end = ptr[1];

	for (start; start <= end; start++)
	{
		total += start;	//위험한 행동, 공유메모리에 락도 없이 접근
	}
	return 0;
}
int ThreadAdder2()
{
	DWORD dwThreadID[3];
	HANDLE hThread[3];

	DWORD paramThread[] = { 1, 30, 31, 70, 71, 100 };
	
	for (int i = 0; i < 3; i++)
	{
		hThread[i] = CreateThread(NULL, 0, ThreadProc2, &paramThread[2 * i], 0, &dwThreadID[i]);
	}

	if (hThread[0] == NULL || hThread[1] == NULL || hThread[2] == NULL)
	{
		_tprintf_s(_T("Creation Thread fault!\n"));
		return -1;
	}

	WaitForMultipleObjects(3, hThread, true, INFINITE);
	_tprintf_s(_T("total (1 ~ 10): %d"), total);
	for (int i = 0; i < 3; i++)
		CloseHandle(hThread[i]);
	return 0;
}

static unsigned ThreadProc3(void* lpParam)
{
	int* ptr = (int*)lpParam;
	int start = ptr[0];
	int end = ptr[1];
	for (start; start <= end; start++)
	{
		total += start;
	}
	return 0;
}
int ThreadAdder3()
{
	unsigned dwThreadID[4];
	HANDLE hThread[4];

	DWORD paramThread[] = { 1, 250, 251, 500, 501, 750, 751, 1000 };

	for (int i = 0; i < 4; i++)
	{
		hThread[i] = (HANDLE)_beginthreadex(nullptr, 0, ThreadProc3, &paramThread[i*2], 0, &dwThreadID[i]);
	}

	if (hThread[0] == nullptr || hThread[1] == nullptr || hThread[2] == nullptr || hThread[3] == nullptr)
	{
		_tprintf_s(_T("Create Thread failed\n"));
		return -1;
	}
	WaitForMultipleObjects(4, hThread, true, INFINITE);

	for (int i = 0; i < 4; i++)
	{
		CloseHandle(hThread[i]);
	}
	_tprintf_s(_T("total(1~1000): %d"), total);
	return 0;
}

static unsigned ImRunning(void* lp)
{
	while (1)
	{
		_tprintf_s(_T("Im RUnning!\n"));
		Sleep(100);
	}
	return 0;
}
int SuspendCount()
{
	unsigned ThreadID;
	HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, ImRunning, nullptr, CREATE_SUSPENDED, &ThreadID);
	if (hThread == nullptr)
	{
		_tprintf_s(_T("Create failed"));
		return -1;
	}
	int susCnt;
	susCnt = ResumeThread(hThread);
	_tprintf_s(_T("susCnt: %d\n"), susCnt);
	Sleep(1000);

	susCnt = SuspendThread(hThread);
	_tprintf_s(_T("susCnt: %d\n"), susCnt);
	Sleep(1000);
	susCnt = SuspendThread(hThread);
	_tprintf_s(_T("susCnt: %d\n"), susCnt);
	Sleep(1000);

	susCnt = ResumeThread(hThread);
	_tprintf_s(_T("susCnt: %d\n"), susCnt);
	Sleep(1000);
	susCnt = ResumeThread(hThread);
	_tprintf_s(_T("susCnt: %d\n"), susCnt);
	Sleep(1000);
	
	_tprintf_s(_T("susCnt: %d\n"), --susCnt);
	CloseHandle(hThread);
	Sleep(1000);
	return 0;
}