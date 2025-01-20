#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include "Ch03.h"

static UINT CallDist(UINT a, UINT b)
{
	return a - b;
}

static UINT_PTR CallDistance(UINT_PTR a, UINT_PTR b)
{
	return a - b;
}

void Ex01()
{
	INT val1 = 10;
	INT val2 = 20;

	_tprintf(_T("Position %x, %x \n"), (UINT)&val1, (UINT)&val2);
	_tprintf(
		_T("Distance : %x \n"), CallDist((UINT)&val1, (UINT)&val2)
	);
}

void Ex02()
{
	UINT_PTR a = 1;
	UINT_PTR b = 2;

	_tprintf(_T("Position %llx, %llx\n"), (UINT_PTR)&a, (UINT_PTR)&b);
	_tprintf(
		_T("Distance : %x \n"), CallDistance((UINT_PTR)&a, (UINT_PTR)&b)
	);
}

void Ex03()
{
	HANDLE hFile = CreateFile(	//Windows �ý��� �Լ�
		_T("ABC.DAT"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
	NULL );
	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("error code: %d \n"), GetLastError());
		// error code 2 :  The system cannot find the file specified
	}
}

void Ex04()
{
	HANDLE hFile = CreateFile(	// GetLastError() �� �ݵ�� ���� ȣ���� �ϱ⸦ �ٶ���.
		_T("ABC2.DAT"), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL,
	NULL);
	_tprintf(_T("error code: %d \n"), GetLastError());
	//�����ϴ� �����̶�� ���� �� 80������ ����. : The file exists
}

void Ex05()
{
	/*
		CreateProcess : ���� ���α׷��� ����
	*/
#define DIR_LEN MAX_PATH+1

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;

	si.cb = sizeof(si);
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	si.dwX = 200;
	si.dwY = 100;
	si.dwXSize = 400;
	si.dwYSize = 400;
	si.lpTitle = (LPWSTR)_T("I am a boy!");
	
	TCHAR command[] = _T("ChildProcess.exe 10 20");
	TCHAR cDir[DIR_LEN];
	BOOL state;

	GetCurrentDirectory(DIR_LEN, cDir);	//���� ���͸� Ȯ��
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	SetCurrentDirectory(_T("C:\\WinSystem"));

	GetCurrentDirectory(DIR_LEN, cDir);	//���� ���͸� Ȯ��
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	state = CreateProcess(
		NULL,
		command,
		NULL, NULL, NULL,
		//0,
		CREATE_NEW_CONSOLE,
		NULL, NULL, &si, &pi
	);

	if (state != 0)
		_fputts(_T("Creation OK! \n"), stdout);
	else
		_fputts(_T("Creation Error! \n"), stdout);
	_gettchar();
}

void Ex06()
{
	/*
		Ex06
		�ý��� ���͸��� Windows ���͸� Ȯ��
	*/

#define DIR_LEN MAX_PATH+1
	TCHAR sysDir[DIR_LEN];
	TCHAR winDir[DIR_LEN];

	GetSystemDirectory(sysDir, DIR_LEN);

	GetWindowsDirectory(winDir, DIR_LEN);

	_tprintf(_T("System Dir: %s \n"), sysDir);
	_tprintf(_T("Windows Dir: %s \n"), winDir);

}