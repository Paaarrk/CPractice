#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include "Ch07.h"

int MailSender()
{
	HANDLE hMailSlot;
	TCHAR message[50];
	DWORD bytesWritten;	//number of bytes write

	hMailSlot = CreateFile(
		SLOT_NAME,	//mailslot's name
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,	//파일 생성 방식
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hMailSlot == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot!\n"), stdout);
		return 1;
	}

	while (1)
	{
		_fputts(_T("My CMD>"), stdout);
		_fgetts(message, sizeof(message) / sizeof(TCHAR) - 1, stdin);

		if (!WriteFile(hMailSlot, message,
			_tcslen(message) * sizeof(TCHAR), &bytesWritten, NULL))
		{
			_fputts(_T("Unable to wwrite!"), stdout);
			return 1;
		}

		if (!_tcsncmp(message, _T("exit"), 4))
		{
			_fputts(_T("Good Bye!"), stdout);
			break;
		}
	}
	getchar();
	CloseHandle(hMailSlot);
	return 0;
}

int NonStopAdderManager()
{
	STARTUPINFO si1 = { 0, };
	STARTUPINFO si2 = { 0, };

	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;

	DWORD return_val1;
	DWORD return_val2;

	TCHAR command1[] = _T("ChildProcess.exe 1 5");
	TCHAR command2[] = _T("ChildProcess.exe 6 10");

	DWORD sum = 0;

	si1.cb = sizeof(si1);
	si2.cb = sizeof(si2);

	CreateProcess(NULL, command1, NULL, NULL, TRUE,
		0, NULL, NULL, &si1, &pi1);
	CreateProcess(NULL, command2, NULL, NULL, TRUE,
		0, NULL, NULL, &si2, &pi2);

	CloseHandle(pi1.hThread);
	CloseHandle(pi2.hThread);

#define HANDLE_COUNT 2
	HANDLE lpHandle[HANDLE_COUNT] = { pi1.hProcess, pi2.hProcess };

	//WaitForSingleObject(pi1.hProcess, INFINITE);
	//WaitForSingleObject(pi2.hProcess, INFINITE);
	WaitForMultipleObjects(HANDLE_COUNT, lpHandle, TRUE, INFINITE);

	GetExitCodeProcess(pi1.hProcess, &return_val1);
	GetExitCodeProcess(pi2.hProcess, &return_val2);

	if (return_val1 == -1 || return_val2 == -1)
		return -1;	//비정상 종료

	sum += return_val1;
	sum += return_val2;

	_tprintf_s(_T("total : %d\n"), sum);

	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);
}