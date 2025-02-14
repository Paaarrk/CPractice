#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <conio.h>
#include "ch08.h"

#define BUF_SIZE 1024

int NamedpipeClient()
{
	HANDLE hPipe;
	TCHAR readDataBuf[BUF_SIZE + 1];
	LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");

	while (true)
	{
		hPipe = CreateFile(
			pipeName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL
		);

		if (hPipe != INVALID_HANDLE_VALUE)
			break;

		if (GetLastError() != ERROR_PIPE_BUSY)
		{
			_tprintf_s(_T("Could not open pipe \n"));
			return 0;
		}

		if (!WaitNamedPipe(pipeName, 20000))
		{
			_tprintf_s(_T("Could not open pipe \n"));
			return 0;
		}
	}

	DWORD pipeMode = PIPE_READMODE_MESSAGE | PIPE_WAIT;
	BOOL isSuccess = SetNamedPipeHandleState(
		hPipe, &pipeMode, NULL, NULL);

	if (!isSuccess)
	{
		_tprintf_s(_T("SetNamedPipeHandleState failed\n"));
		return 0;
	}

	LPCTSTR fileName = _T("news.txt");
	DWORD bytesWritten = 0;

	isSuccess = WriteFile(
		hPipe,
		fileName,
		(_tcsclen(fileName) + 1) * sizeof(TCHAR),
		&bytesWritten,
		NULL);

	if (!isSuccess)
	{
		_tprintf_s(_T("WriteFile failed\n"));
		return 0;
	}

	DWORD bytesRead = 0;
	while (true)
	{
		isSuccess = ReadFile(
			hPipe,
			readDataBuf,
			BUF_SIZE * sizeof(TCHAR),
			&bytesRead,
			NULL);

		if (!isSuccess && GetLastError() != ERROR_MORE_DATA)
			break;

		readDataBuf[bytesRead] = 0;
		_tprintf_s(_T("%s \n"), readDataBuf);
	}

	CloseHandle(hPipe);
	_getch();
	return 0;
}

int EnvChild()
{
	TCHAR value[BUF_SIZE];
	if (GetEnvironmentVariable(_T("Good"), value, BUF_SIZE) > 0)
		_tprintf_s(_T("[%s = %s]\n"), _T("Good"), value);
	if (GetEnvironmentVariable(_T("Hey"), value, BUF_SIZE) > 0)
		_tprintf_s(_T("[%s = %s]\n"), _T("Hey"), value);
	if (GetEnvironmentVariable(_T("Big"), value, BUF_SIZE) > 0)
		_tprintf_s(_T("[%s = %s]\n"), _T("Big"), value);

	Sleep(10000);
	return 0;
}