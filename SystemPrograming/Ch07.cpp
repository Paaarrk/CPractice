
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

int MailSenderWithChild()
{
	HANDLE hMailslot;
	TCHAR message[50];
	DWORD bytesWritten;

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = true;

	hMailslot = CreateFile(
		SLOT_NAME, GENERIC_WRITE, FILE_SHARE_READ,
		&sa, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hMailslot == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot! \n"), stdout);
		return 1;
	}

	_tprintf_s(_T("Inheritable Handle : %llx \n"), (long long)hMailslot);
	FILE* file;
	_tfopen_s(&file, _T("InheritableHandle.txt"), _T("wt"));
	_ftprintf(file, _T("%llx"), (long long)hMailslot);
	fclose(file);

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("SenderChild.exe");
	CreateProcess(NULL, command, 
		NULL, NULL,
		TRUE,	//Handle의 상속
		CREATE_NEW_CONSOLE,
		NULL, NULL,
		&si, &pi); //Create Process

	while (1)
	{
		_fputts(_T("MY CMD>"), stdout);
		_fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);
		if (!WriteFile(
			hMailslot, message, _tcslen(message) * sizeof(TCHAR),
			&bytesWritten, NULL))
		{
			_fputts(_T("Unable to write!"), stdout);
			CloseHandle(hMailslot);
			return 1;
		}

		if (!_tcscmp(message, _T("exit")))
		{
			_fputts(_T("Good Bye!"), stdout);
			break;
		}
	}
	CloseHandle(hMailslot);
	return 0;
}

int MailSenderChild()
{
	HANDLE hMailSlot;
	TCHAR message[50];
	DWORD bytesWritten;


	FILE* file;
	_tfopen_s(&file, _T("InheritableHandle.txt"), _T("rt"));
	_ftscanf_s(file, _T("%llx"), (long long) &hMailSlot);
	fclose(file);
	_tprintf_s(_T("Inheritable Handle : %llx"), (long long)hMailSlot);

	while (1)
	{
		_fputts(_T("MY CMD>"), stdout);
		_fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);
		if (!WriteFile(
			hMailSlot, message, _tcslen(message) * sizeof(TCHAR),
			&bytesWritten, NULL))
		{
			_fputts(_T("Unable to write!"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}

		if (!_tcscmp(message, _T("exit")))
		{
			_fputts(_T("Good Bye!"), stdout);
			break;
		}
	}
	CloseHandle(hMailSlot);
	return 0;
}


int DuplicateHandle()
{
	HANDLE hProcess;
	TCHAR cmdString[1024];

	DuplicateHandle(GetCurrentProcess(), GetCurrentProcess(),
		GetCurrentProcess(), &hProcess, 0, TRUE,
		DUPLICATE_SAME_ACCESS);

	_stprintf_s(
		cmdString, _T("%s %p"), _T("ChildProcess.exe"), hProcess);

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };
	si.cb = sizeof(si);

	BOOL isSuccess = CreateProcess(
		NULL, cmdString, NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	
	if (isSuccess == FALSE)
	{
		_tprintf(_T("CreateProcess failed\n"));
		return -1;
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	_tprintf_s(_T("[Parent Process]\n"));
	_tprintf_s(_T("oooooooooooooooooooooooooooops!\n"));
	return 0;
}